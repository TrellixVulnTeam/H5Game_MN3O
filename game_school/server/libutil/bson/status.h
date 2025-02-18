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

#include "pw_def.h"
#include "mongo/string_data.h"

namespace mongo {

    /**
     * Status represents an error state or the absence thereof.
     *
     * A Status uses the standardized error codes -- from file 'error_codes.h' -- to
     * determine an error's cause. It further clarifies the error with a textual
     * description. Optionally, a Status may also have an error location number, which
     * should be a unique, grep-able point in the code base (including assert numbers).
     *
     * Example usage:
     *
     *    Status sumAB(int a, int b, int* c) {
     *       if (overflowIfSum(a,b)) {
     *           return Status(ErrorCodes::ERROR_OVERFLOW, "overflow in sumAB", 16494);
     *       }
     *
     *       *c = a+b;
     *       return Status::OK();
     *   }
     *
     * TODO: expand base/error_codes.h to capture common errors in current code
     * TODO: generate base/error_codes.h out of a description file
     * TODO: check 'location' duplicates against assert numbers
     */
    class Status {
    public:
        // Short-hand for returning an OK status.
        static inline Status OK();

        /**
         * Builds an error status given the error code, a textual description of what
         * caused the error, and a unique position in the where the error occurred
         * (similar to an assert number)
         */
        Status(unsigned code, const std::string& reason, int location = 0);
        Status(unsigned code, const char* reason, int location = 0);

        inline Status(const Status& other);
        inline Status& operator=(const Status& other);

#if __cplusplus >= 201103L
        inline Status(Status&& other) noexcept;
        inline Status& operator=(Status&& other) noexcept;
#endif // __cplusplus >= 201103L

        inline ~Status();

        /**
         * Returns true if 'other's error code and location are equal/different to this
         * instance's. Otherwise returns false.
         */
        bool compare(const Status& other) const;
        bool operator==(const Status& other) const;
        bool operator!=(const Status& other) const;

        /**
         * Returns true if 'other's error code is equal/different to this instance's.
         * Otherwise returns false.
         */
        bool compareCode(const unsigned other) const;
        bool operator==(const unsigned other) const;
        bool operator!=(const unsigned other) const;

        //
        // accessors
        //

        inline bool isOK() const;

        inline unsigned code() const;

        inline std::string codeString() const;

        inline std::string reason() const;

        inline int location() const;

        std::string toString() const;

        //
        // Below interface used for testing code only.
        //

    private:
        inline Status();

		struct ErrorInfo {
            unsigned code;  // error code
            std::string reason;      // description of error cause
            int location;            // unique location of the triggering line in the code

            ErrorInfo(unsigned code, const StringData& reason, int location);
        };

        ErrorInfo _error;

        /**
         * Increment/Decrement the reference counter inside an ErrorInfo
         *
         * @param error  ErrorInfo to be incremented
         */
        static inline void ref(ErrorInfo* error);
        static inline void unref(ErrorInfo* error);
    };

    inline bool operator==(const unsigned lhs, const Status& rhs);

    inline bool operator!=(const unsigned lhs, const Status& rhs);

    //
    // Convenience method for unittest code. Please use accessors otherwise.
    //

    std::ostream& operator<<(std::ostream& os, const Status& status);
    std::ostream& operator<<(std::ostream& os, unsigned);

}  // namespace mongo

#include "status-inl.h"
