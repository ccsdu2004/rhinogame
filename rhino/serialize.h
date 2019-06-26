#ifndef RHINO_SERIALIZE_H
#define RHINO_SERIALIZE_H
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#define RHINO_REFLECT_MEMBER_OP(r,OP,elem)\
    OP t.elem

#define RHINO_SERIALIZE(TYPE,MEMBERS)\
    template<typename DataStream>\
    friend DataStream& operator << (DataStream& ds, const TYPE& t){ \
        return ds BOOST_PP_SEQ_FOR_EACH( EOSLIB_REFLECT_MEMBER_OP, <<, MEMBERS );\
    }\
    template<typename DataStream> \
    friend DataStream& operator >> ( DataStream& ds, TYPE& t ){ \
        return ds BOOST_PP_SEQ_FOR_EACH( EOSLIB_REFLECT_MEMBER_OP, >>, MEMBERS );\
    }

    #define RHINO_SERIALIZE_DERIVED(TYPE, BASE, MEMBERS) \
    template<typename DataStream> \
    friend DataStream& operator << ( DataStream& ds, const TYPE& t ){ \
        ds << static_cast<const BASE&>(t); \
        return ds BOOST_PP_SEQ_FOR_EACH( EOSLIB_REFLECT_MEMBER_OP, <<, MEMBERS );\
    }\
    template<typename DataStream> \
    friend DataStream& operator >> ( DataStream& ds, TYPE& t ){ \
       ds >> static_cast<BASE&>(t); \
       return ds BOOST_PP_SEQ_FOR_EACH( EOSLIB_REFLECT_MEMBER_OP, >>, MEMBERS );\
    }

#endif