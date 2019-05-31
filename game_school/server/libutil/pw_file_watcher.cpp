#include "pw_file_watcher.h"

#ifndef _MSC_VER

namespace pwutils
{


	FileWatcher::FileWatcher()
	{
		m_fd = inotify_init();
	}

	FileWatcher::~FileWatcher()
	{
		close(m_fd);
	}

	int FileWatcher::Add( const std::string& path,unsigned mask )
	{
		int wd = inotify_add_watch(m_fd,path.c_str(),mask);
		if( wd <= 0)
			return wd;

		SWatchInfo info;
		info.path = path;
		info.wd = wd;
		m_vInfos.push_back(info);

		return wd;
	}

	int FileWatcher::Del( const std::string& path )
	{
		for(size_t i = 0; i < m_vInfos.size(); ++i)
		{
			SWatchInfo& rinfo = m_vInfos[i];
			if(rinfo.path == path)
				return this->Del(rinfo.wd);
		}
		return -1;
	}

	int FileWatcher::Del( int wd )
	{
		if(inotify_rm_watch(m_fd,wd) == 0)
		{
			for(size_t i = 0; i < m_vInfos.size(); ++i)
			{
				SWatchInfo& rinfo = m_vInfos[i];
				if(rinfo.wd == wd)
				{
					m_vInfos.erase(m_vInfos.begin() + i);
					return 0;
				}
			}
		}
		return -1;
	}

	int FileWatcher::Update()
	{
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(m_fd,&fds);

		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 1000;
		if(select(m_fd+1,&fds,NULL,NULL,&tv) > 0)
		{
			char tmpbuf[102400] = {0};
			char* evtbuf = tmpbuf;
			ssize_t size = read(m_fd,tmpbuf,sizeof(tmpbuf));
			while(size > 0)
			{
				struct inotify_event* evt = (struct inotify_event*)evtbuf;
				this->HandleEvent(evt->mask,evt->name);
				evtbuf += sizeof(struct inotify_event) + evt->len;
				size -= sizeof(struct inotify_event) + evt->len;
			}
		}
		return 0;
	}

}

#endif