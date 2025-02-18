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

#include "mongo/string_data.h"

#include <ostream>
//#include <third_party/murmurhash3/MurmurHash3.h>

namespace mongo {

//     namespace {
// 
//         template <int SizeofSizeT>
//         size_t murmur3(const StringData& str);
// 
//         template <>
//         size_t murmur3<4>(const StringData& str) {
//             uint32_t hash;
//             MurmurHash3_x86_32(str.rawData(), str.size(), 0, &hash);
//             return hash;
//         }
// 
//         template <>
//         size_t murmur3<8>(const StringData& str) {
//             uint64_t hash[2];
//             MurmurHash3_x64_128(str.rawData(), str.size(), 0, hash);
//             return static_cast<size_t>(hash[0]);
//         }
// 
//     }  // namespace

    std::ostream& operator<<(std::ostream& stream, const StringData& value) {
        return stream.write(value.rawData(), value.size());
    }

//     size_t StringData::Hasher::operator() (const StringData& str) const {
//         return murmur3<sizeof(size_t)>(str);
//     }

} // namespace mongo
