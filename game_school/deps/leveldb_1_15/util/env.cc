// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "leveldb/env.h"

namespace leveldb {

Env::~Env() {
}

SequentialFile::~SequentialFile() {
}

RandomAccessFile::~RandomAccessFile() {
}

WritableFile::~WritableFile() {
}

Logger::~Logger() {
}

FileLock::~FileLock() {
}

void Log(Logger* info_log, const char* format, ...) {
  if (info_log != NULL) {
    va_list ap;
    va_start(ap, format);
    info_log->Logv(format, ap);
    va_end(ap);
  }
}

static Status DoWriteStringToFile(Env* env, const Slice& data,
                                  const std::string& fname,
                                  bool should_sync) {
  WritableFile* file;
  Status s = env->NewWritableFile(fname, &file);
  if (!s.ok()) {
    return s;
  }
  s = file->Append(data);
  if (s.ok() && should_sync) {
    s = file->Sync();
  }
  if (s.ok()) {
    s = file->Close();
  }
  delete file;  // Will auto-close if we did not close above
  if (!s.ok()) {
    env->DeleteFile(fname);
  }
  return s;
}

Status WriteStringToFile(Env* env, const Slice& data,
                         const std::string& fname) {
  return DoWriteStringToFile(env, data, fname, false);
}

Status WriteStringToFileSync(Env* env, const Slice& data,
                             const std::string& fname) {
  return DoWriteStringToFile(env, data, fname, true);
}

Status ReadFileToString(Env* env, const std::string& fname, std::string* data) {
  data->clear();
  SequentialFile* file;
  Status s = env->NewSequentialFile(fname, &file);
  if (!s.ok()) {
    return s;
  }
  static const int kBufferSize = 8192;
  char* space = new char[kBufferSize];
  while (true) {
    Slice fragment;
    s = file->Read(kBufferSize, &fragment, space);
    if (!s.ok()) {
      break;
    }
    data->append(fragment.data(), fragment.size());
    if (fragment.empty()) {
      break;
    }
  }
  delete[] space;
  delete file;
  return s;
}

EnvWrapper::~EnvWrapper() {
}

}  // namespace leveldb


#include "port/port.h"
#include "db/filename.h"

namespace leveldb {

	class BackupEnv : public leveldb::EnvWrapper {
	private:
		port::Mutex mu_;
		bool backing_up_;
		std::vector<std::string> deferred_deletions_;

	public:
		explicit BackupEnv(leveldb::Env* t)
			: leveldb::EnvWrapper(t), backing_up_(false) {
		}

		Status DeleteFile(const std::string& f);

		// Call (*save)(arg, filename, length) for every file that
		// should be backed up to construct a consistent view of the
		// database.  "length" may be negative to indicate that the entire
		// file must be copied.  Otherwise the first "length" bytes must be
		// copied.
		Status Backup(const std::string& dir,
			int (*func)(void*, const char* fname, uint64_t length),
			void* arg);

		bool CopyFile(const std::string& fname);
		bool KeepFile(const std::string& fname);
	};

	Status BackupEnv::DeleteFile(const std::string& f) {
		mu_.Lock();
		Status s;
		if (backing_up_) {
			deferred_deletions_.push_back(f);
		} else {
			s = target()->DeleteFile(f);
		}
		mu_.Unlock();
		return s;
	}

	// Call (*save)(arg, filename, length) for every file that
	// should be backed up to construct a consistent view of the
	// database.  "length" may be negative to indicate that the entire
	// file must be copied.  Otherwise the first "length" bytes must be
	// copied.
	Status BackupEnv::Backup(const std::string& dir,
		int (*func)(void*, const char* fname, uint64_t length),
		void* arg) {
			// Get a consistent view of all files.
			mu_.Lock();
			std::vector<std::string> files;
			Status s = GetChildren(dir, &files);
			if (!s.ok()) {
				mu_.Unlock();
				return s;
			}
			std::vector<uint64_t> lengths(files.size());
			for (size_t i = 0; i < files.size(); i++) {
				if (files[i][0] == '.') {
					continue;
				}
				if (CopyFile(files[i])) {
					uint64_t len;
					s = GetFileSize(dir + "/" + files[i], &len);
					if (!s.ok()) {
						mu_.Unlock();
						return s;
					}
					lengths[i] = len;
				} else {
					lengths[i] = -1;
				}
			}
			backing_up_ = true;
			mu_.Unlock();

			for (size_t i = 0; s.ok() && i < files.size(); i++) {
				if (KeepFile(files[i])) {
					if ((*func)(arg, files[i].c_str(), lengths[i]) != 0) {
						s = Status::IOError("backup failed");
						break;
					}
				}
			}

			mu_.Lock();
			backing_up_ = false;
			for (size_t i = 0; i < deferred_deletions_.size(); i++) {
				target()->DeleteFile(deferred_deletions_[i]);
			}
			deferred_deletions_.clear();
			mu_.Unlock();

			return s;
	}

	bool BackupEnv::CopyFile(const std::string& fname) {
		uint64_t number;
		FileType type;
		ParseFileName(fname, &number, &type);
		return type != kTableFile && type != kDBLockFile;
	}

	bool BackupEnv::KeepFile(const std::string& fname) {
		uint64_t number;
		FileType type;
		if (ParseFileName(fname, &number, &type)) {
			switch (type) {
		case kLogFile:
		case kTableFile:
		case kDescriptorFile:
		case kCurrentFile:
		case kInfoLogFile:
			return true;
			}
		}
		return false;
	}

	Env* NewBackupEnv(Env* target)
	{
		return new BackupEnv(target);
	}

	Status BackupDatabase( Env* backup_env,const std::string& dir, int (*func)(void*, const char* fname, uint64_t length), void* arg )
	{
		BackupEnv* actualEnv = (BackupEnv*)backup_env;
		return actualEnv->Backup(dir,func,arg);
	}

} // end namespace leveldb
