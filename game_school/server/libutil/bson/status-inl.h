/*    Copyright 2012 10gen Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

namespace mongo {

    inline Status Status::OK() {
        return Status();
    }

    inline Status::Status(const Status& other)
        : _error(other._error) {
    }

    inline Status& Status::operator=(const Status& other) {
        _error = other._error;
        return *this;
    }

    inline Status::~Status() {
    }

    inline bool Status::isOK() const {
        return code() == 0;
    }

    inline unsigned Status::code() const {
        return _error.code;
    }

    inline std::string Status::codeString() const {
        return this->_error.reason;
    }

    inline std::string Status::reason() const {
        return _error.reason;
    }

    inline int Status::location() const {
        return _error.location;
    }

    inline Status::Status()
        : _error(0,"",0) {
    }

    inline bool operator==(const unsigned lhs, const Status& rhs) {
        return rhs == lhs;
    }

    inline bool operator!=(const unsigned lhs, const Status& rhs) {
        return rhs != lhs;
    }

} // namespace mongo
