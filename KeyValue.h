//
// Created by finea on 3/30/2017.
//

#ifndef GENERIC_DICTIONARY_KEYVALUE_H
#define GENERIC_DICTIONARY_KEYVALUE_H

#include <algorithm>
#include <ostream>

template < typename Key, typename Data >
class KeyValue
{

private:
    Key key;
    Data data;
public:

    KeyValue( Key initialKey, Data initialData );// Base Constructor

    KeyValue( KeyValue& rhs );                   // Copy constructor
    KeyValue( KeyValue&& rhs );                  // Move constructor
    KeyValue& operator=( KeyValue& rhs );        // Copy assignment
    KeyValue& operator=( KeyValue&& rhs );       // Move assignment

    bool operator<( const KeyValue& rhs ) const;

    bool operator<=( const KeyValue& rhs ) const;

    bool operator>( const KeyValue& rhs ) const;

    bool operator>=( const KeyValue& rhs ) const;

    bool operator==( const KeyValue& rhs ) const;

    const Key& getKey() const
    { return key; }

    Data& getData()
    { return data; }

    void setData(Data input)
    {
        data = input;
    }

    KeyValue& access()
    { return *this; }

    void display( std::ostream& out ) const
    {
        out << "Key: " << key << " Data: " << data << "\n";
    }

    friend std::ostream& operator<<( std::ostream& out, KeyValue rhs )
    {
        out << "[" << rhs.getKey() << ", " << rhs.getData() << "]";
        return out;
    }

};

template < typename Key, typename Data >
KeyValue< Key, Data >::KeyValue( KeyValue& rhs ) :
        key( rhs.getKey()),
        data( rhs.getData())
{
    //Empty
}

template < typename Key, typename Data >
KeyValue< Key, Data >::KeyValue( KeyValue&& rhs ) :
        key( rhs.getKey()),
        data( rhs.getData())
{
    //Empty
}

template < typename Key, typename Data >
KeyValue< Key, Data >& KeyValue< Key, Data >::operator=( KeyValue& rhs )
{
    if ( this != &rhs )
    {
        key = rhs.getKey();
        data = rhs.getData();
    }
    return *this;
}

template < typename Key, typename Data >
KeyValue< Key, Data >& KeyValue< Key, Data >::operator=( KeyValue&& rhs )
{
    std::swap( key, rhs.key );
    std::swap( data, rhs.data );
    return *this;
}

template < typename Key, typename Data >
KeyValue< Key, Data >::KeyValue( Key initialKey, Data initialData ):
        key( initialKey ),
        data( initialData )
{
    // Empty
}

template < typename Key, typename Data >
bool KeyValue< Key, Data >::operator<( const KeyValue& rhs ) const
{
    return getKey() < rhs.getKey();
}

template < typename Key, typename Data >
bool KeyValue< Key, Data >::operator<=( const KeyValue& rhs ) const
{
    return getKey() <= rhs.getKey();
}

template < typename Key, typename Data >
bool KeyValue< Key, Data >::operator>( const KeyValue& rhs ) const
{
    return getKey() > rhs.getKey();
}

template < typename Key, typename Data >
bool KeyValue< Key, Data >::operator>=( const KeyValue& rhs ) const
{
    return getKey() >= rhs.getKey();
}

template < typename Key, typename Data >
bool KeyValue< Key, Data >::operator==( const KeyValue& rhs ) const
{
    return getKey() == rhs.getKey();
}

#endif //GENERIC_DICTIONARY_KEYVALUE_H
