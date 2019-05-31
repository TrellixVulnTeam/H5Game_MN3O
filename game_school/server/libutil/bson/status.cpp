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

#include "status.h"

#include <ostream>
#include <sstream>

namespace mongo {

    Status::ErrorInfo::ErrorInfo(unsigned aCode, const StringData& aReason, int aLocation)
        : code(aCode), reason(aReason.toString()), location(aLocation) {
    }

    Status::Status(unsigned code, const std::string& reason, int location)
        : _error(code, reason, location) {
    }

    Status::Status(unsigned code, const char* reason, int location)
        : _error(code, reason, location) {
    }

    bool Status::compare(const Status& other) const {
        return
            code() == other.code() &&
            location() == other.location();
    }

    bool Status::operator==(const Status& other) const {
        return compare(other);
    }

    bool Status::operator!=(const Status& other) const {
        return ! compare(other);
    }

    bool Status::compareCode(const unsigned other) const {
        return code() == other;
    }

    bool Status::operator==(const unsigned other) const {
        return compareCode(other);
    }

    bool Status::operator!=(const unsigned other) const {
        return ! compareCode(other);
    }

    std::ostream& operator<<(std::ostream& os, const Status& status) {
        return os << status.codeString() << " " << status.reason();
    }

    std::ostream& operator<<(std::ostream& os, unsigned code) {
        return os << (int)code;
    }

    std::string Status::toString() const {
        std::ostringstream ss;
        ss << codeString();
        if ( !isOK() )
            ss << " " << reason();
        if ( location() != 0 )
            ss << " @ " << location();
        return ss.str();
    }

} // namespace mongo
