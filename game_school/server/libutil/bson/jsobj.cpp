/** @file jsobj.cpp - BSON implementation
    http://dochub.mongodb.org/core/bson
*/

/*    Copyright 2009 10gen Inc.
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

#include "pw_types.h"
#include "bson.h"
#include <strstream>
#include <algorithm>
#include "mongo/string_data.h"


// make sure our assumptions are valid
// BOOST_STATIC_ASSERT( sizeof(short) == 2 );
// BOOST_STATIC_ASSERT( sizeof(int) == 4 );
// BOOST_STATIC_ASSERT( sizeof(long long) == 8 );
// BOOST_STATIC_ASSERT( sizeof(double) == 8 );
// BOOST_STATIC_ASSERT( sizeof(mongo::Date_t) == 8 );
// BOOST_STATIC_ASSERT( sizeof(mongo::OID) == 12 );

namespace mongo {

	using namespace std;

	template<class T,class U> T lexical_cast(const U& u)
	{
		std::stringstream ss;
		ss << u;
		T result;
		ss >> result;
		return result;
	}

	
    // need to move to bson/, but has dependency on base64 so move that to bson/util/ first.
    inline string BSONElement::jsonString( JsonStringFormat format, bool includeFieldNames, int pretty ) const {
        int sign;

        stringstream s;
        if ( includeFieldNames )
            s << '"' << escape( fieldName() ) << "\" : ";
        switch ( type() ) {
        case mongo::String:
        case Symbol:
            s << '"' << escape( string(valuestr(), valuestrsize()-1) ) << '"';
            break;
        case NumberLong:
            if (format == TenGen) {
                s << "NumberLong(" << _numberLong() << ")";
            }
            else {
                s << "{ \"$numberLong\" : \"" << _numberLong() << "\" }";
            }
            break;
        case NumberInt:
            if(format == JS) {
                s << "NumberInt(" << _numberInt() << ")";
                break;
            }
        case NumberDouble:
            if ( number() >= -numeric_limits< double >::max() &&
                    number() <= numeric_limits< double >::max() ) {
                s.precision( 16 );
                s << number();
            }
            // This is not valid JSON, but according to RFC-4627, "Numeric values that cannot be
            // represented as sequences of digits (such as Infinity and NaN) are not permitted." so
            // we are accepting the fact that if we have such values we cannot output valid JSON.
            else if ( mongo::isNaN(number()) ) {
                s << "NaN";
            }
            else if ( mongo::isInf(number(), &sign) ) {
                s << ( sign == 1 ? "Infinity" : "-Infinity");
            }
            else {
                StringBuilder ss;
                ss << "Number " << number() << " cannot be represented in JSON";
                string message = ss.str();
                massert( 10311 ,  message.c_str(), false );
            }
            break;
        case mongo::Bool:
            s << ( boolean() ? "true" : "false" );
            break;
        case jstNULL:
            s << "null";
            break;
        case Undefined:
            if ( format == Strict ) {
                s << "{ \"$undefined\" : true }";
            }
            else {
                s << "undefined";
            }
            break;
        case Object:
            s << embeddedObject().jsonString( format, pretty );
            break;
        case mongo::Array: {
            if ( embeddedObject().isEmpty() ) {
                s << "[]";
                break;
            }
            s << "[ ";
            BSONObjIterator i( embeddedObject() );
            BSONElement e = i.next();
            if ( !e.eoo() ) {
                int count = 0;
                while ( 1 ) {
                    if( pretty ) {
                        s << '\n';
                        for( int x = 0; x < pretty; x++ )
                            s << "  ";
                    }

                    if (strtol(e.fieldName(), 0, 10) > count) {
                        s << "undefined";
                    }
                    else {
                        s << e.jsonString( format, false, pretty?pretty+1:0 );
                        e = i.next();
                    }
                    count++;
                    if ( e.eoo() )
                        break;
                    s << ", ";
                }
            }
            s << " ]";
            break;
        }
/*
        case DBRef: {
            mongo::OID *x = (mongo::OID *) (valuestr() + valuestrsize());
            if ( format == TenGen )
                s << "Dbref( ";
            else
                s << "{ \"$ref\" : ";
            s << '"' << valuestr() << "\", ";
            if ( format != TenGen )
                s << "\"$id\" : ";
            s << '"' << *x << "\" ";
            if ( format == TenGen )
                s << ')';
            else
                s << '}';
            break;
        }
        case jstOID:
            if ( format == TenGen ) {
                s << "ObjectId( ";
            }
            else {
                s << "{ \"$oid\" : ";
            }
            s << '"' << __oid() << '"';
            if ( format == TenGen ) {
                s << " )";
            }
            else {
                s << " }";
            }
            break;
        case BinData: {
            const int len = *( reinterpret_cast<const int*>( value() ) );
            BinDataType type = BinDataType( *( reinterpret_cast<const unsigned char*>( value() ) +
                                               sizeof( int ) ) );
            s << "{ \"$binary\" : \"";
            const char *start = reinterpret_cast<const char*>( value() ) + sizeof( int ) + 1;
            base64::encode( s , start , len );
            s << "\", \"$type\" : \"" << hex;
            s.width( 2 );
            s.fill( '0' );
            s << type << dec;
            s << "\" }";
            break;
        }
        case mongo::Date:
            if (format == Strict) {
                Date_t d = date();
                s << "{ \"$date\" : ";
                if (static_cast<long long>(d.millis) < 0) {
                    s << "{ \"$numberLong\" : \"" << static_cast<long long>(d.millis) << "\" }";
                }
                else {
                    s << "\"" << dateToISOStringLocal(date()) << "\"";
                }
                s << " }";
            }
            else {
                s << "Date( ";
                if (pretty) {
                    Date_t d = date();
                    if (static_cast<long long>(d.millis) < 0) {
                        // FIXME: This is not parseable by the shell, since it may not fit in a
                        // float
                        s << d.millis;
                    }
                    else {
                        s << "\"" << dateToISOStringLocal(date()) << "\"";
                    }
                }
                else {
                    s << date().asInt64();
                }
                s << " )";
            }
            break;
        case RegEx:
            if ( format == Strict ) {
                s << "{ \"$regex\" : \"" << escape( regex() );
                s << "\", \"$options\" : \"" << regexFlags() << "\" }";
            }
            else {
                s << "/" << escape( regex() , true ) << "/";
                // FIXME Worry about alpha order?
                for ( const char *f = regexFlags(); *f; ++f ) {
                    switch ( *f ) {
                    case 'g':
                    case 'i':
                    case 'm':
                        s << *f;
                    default:
                        break;
                    }
                }
            }
            break;

        case CodeWScope: {
            BSONObj scope = codeWScopeObject();
            if ( ! scope.isEmpty() ) {
                s << "{ \"$code\" : \"" << escape(_asCode()) << "\" , "
                  << "\"$scope\" : " << scope.jsonString() << " }";
                break;
            }
        }
		*/

        case Code:
            s << "\"" << escape(_asCode()) << "\"";
            break;

        case Timestamp:
            if ( format == TenGen ) {
                s << "Timestamp( " << ( timestampTime() / 1000 ) << ", " << timestampInc() << " )";
            }
            else {
                s << "{ \"$timestamp\" : { \"t\" : " << ( timestampTime() / 1000 ) << ", \"i\" : " << timestampInc() << " } }";
            }
            break;

        case MinKey:
            s << "{ \"$minKey\" : 1 }";
            break;

        case MaxKey:
            s << "{ \"$maxKey\" : 1 }";
            break;

        default:
            StringBuilder ss;
            ss << "Cannot create a properly formatted JSON string with "
               << "element: " << toString() << " of type: " << type();
            string message = ss.str();
            massert( 10312 ,  message.c_str(), false );
        }
        return s.str();
    }

    /** Compare two bson elements, provided as const char *'s, by field name. */
    class BSONIteratorSorted::ElementFieldCmp {
    public:
        ElementFieldCmp( bool isArray );
        bool operator()( const char *s1, const char *s2 ) const;
    private:
        LexNumCmp _cmp;
    };
    
    BSONIteratorSorted::ElementFieldCmp::ElementFieldCmp( bool isArray ) :
    _cmp( !isArray ) {
    }

    bool BSONIteratorSorted::ElementFieldCmp::operator()( const char *s1, const char *s2 )
    const {
        // Skip the type byte and compare field names.
        return _cmp( s1 + 1, s2 + 1 );
    }        
    
    BSONIteratorSorted::BSONIteratorSorted( const BSONObj &o, const ElementFieldCmp &cmp ) {
        _nfields = o.nFields();
        _fields = new const char*[_nfields];
        int x = 0;
        BSONObjIterator i( o );
        while ( i.more() ) {
            _fields[x++] = i.next().rawdata();
            verify( _fields[x-1] );
        }
        verify( x == _nfields );
        std::sort( _fields , _fields + _nfields , cmp );
        _cur = 0;
    }
    
    BSONObjIteratorSorted::BSONObjIteratorSorted( const BSONObj &object ) :
    BSONIteratorSorted( object, ElementFieldCmp( false ) ) {
    }

    BSONArrayIteratorSorted::BSONArrayIteratorSorted( const BSONArray &array ) :
    BSONIteratorSorted( array, ElementFieldCmp( true ) ) {
    }

    bool BSONObjBuilder::appendAsNumber( const StringData& fieldName , const string& data ) {
        if ( data.size() == 0 || data == "-" || data == ".")
            return false;

        unsigned int pos=0;
        if ( data[0] == '-' )
            pos++;

        bool hasDec = false;

        for ( ; pos<data.size(); pos++ ) {
            if ( isdigit(data[pos]) )
                continue;

            if ( data[pos] == '.' ) {
                if ( hasDec )
                    return false;
                hasDec = true;
                continue;
            }

            return false;
        }

        if ( hasDec ) {
            double d = atof( data.c_str() );
            append( fieldName , d );
            return true;
        }

        if ( data.size() < 8 ) {
            append( fieldName , atoi( data.c_str() ) );
            return true;
        }

        long long num = lexical_cast<long long>( data );
        append( fieldName , num );
        return true;
    }

    /* take a BSONType and return the name of that type as a char* */
    const char* typeName (BSONType type) {
        switch (type) {
            case MinKey: return "MinKey";
            case EOO: return "EOO";
            case NumberDouble: return "NumberDouble";
            case String: return "String";
            case Object: return "Object";
            case Array: return "Array";
            case BinData: return "BinaryData";
            case Undefined: return "Undefined";
//             case jstOID: return "OID";
            case Bool: return "Bool";
            case Date: return "Date";
            case jstNULL: return "NULL";
            case RegEx: return "RegEx";
            case DBRef: return "DBRef";
            case Code: return "Code";
            case Symbol: return "Symbol";
            case CodeWScope: return "CodeWScope";
            case NumberInt: return "NumberInt32";
            case Timestamp: return "Timestamp";
            case NumberLong: return "NumberLong64";
            // JSTypeMax doesn't make sense to turn into a string; overlaps with highest-valued type
            case MaxKey: return "MaxKey";
            default: return "Invalid";
        }
    }

	LexNumCmp::LexNumCmp( bool lexOnly ) :
	_lexOnly( lexOnly ) {
	}

	int LexNumCmp::cmp( const StringData& sd1, const StringData& sd2, bool lexOnly ) {
		bool startWord = true;

		size_t s1 = 0;
		size_t s2 = 0;

		while( s1 < sd1.size() && s2 < sd2.size() ) {
			bool d1 = ( sd1[s1] == '.' );
			bool d2 = ( sd2[s2] == '.' );
			if ( d1 && !d2 )
				return -1;
			if ( d2 && !d1 )
				return 1;
			if ( d1 && d2 ) {
				++s1; ++s2;
				startWord = true;
				continue;
			}

			bool p1 = ( sd1[s1] == (char)255 );
			bool p2 = ( sd2[s2] == (char)255 );

			if ( p1 && !p2 )
				return 1;
			if ( p2 && !p1 )
				return -1;

			if ( !lexOnly ) {
				bool n1 = isdigit( sd1[s1] );
				bool n2 = isdigit( sd2[s2] );

				if ( n1 && n2 ) {
					// get rid of leading 0s
					if ( startWord ) {
						while ( s1 < sd1.size() && sd1[s1] == '0' ) s1++;
						while ( s2 < sd2.size() && sd2[s2] == '0' ) s2++;
					}

					size_t e1 = s1;
					size_t e2 = s2;

					while ( e1 < sd1.size() && isdigit( sd1[e1] ) ) e1++;
					while ( e2 < sd2.size() && isdigit( sd2[e2] ) ) e2++;

					size_t len1 = e1-s1;
					size_t len2 = e2-s2;

					int result;
					// if one is longer than the other, return
					if ( len1 > len2 ) {
						return 1;
					}
					else if ( len2 > len1 ) {
						return -1;
					}
					// if the lengths are equal, just strcmp
					else {
						result = strncmp( sd1.rawData() + s1,
							sd2.rawData() + s2,
							len1 );
						if ( result )
							return result;
					}

					// otherwise, the numbers are equal
					s1 = e1;
					s2 = e2;
					startWord = false;
					continue;
				}

				if ( n1 )
					return 1;

				if ( n2 )
					return -1;
			}

			if ( sd1[s1] > sd2[s2] )
				return 1;

			if ( sd2[s2] > sd1[s1] )
				return -1;

			s1++; s2++;
			startWord = false;
		}

		if ( s1 < sd1.size() && sd1[s1] )
			return 1;
		if ( s2 < sd2.size() && sd2[s2] )
			return -1;
		return 0;
	}

	int LexNumCmp::cmp( const StringData& s1, const StringData& s2 ) const {
		return cmp( s1, s2, _lexOnly );
	}
	bool LexNumCmp::operator()( const StringData& s1, const StringData& s2 ) const {
		return cmp( s1, s2 ) < 0;
	}
} // namespace mongo
