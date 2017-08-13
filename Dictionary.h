//
// Created by finea on 3/30/2017.
//

#ifndef GENERIC_DICTIONARY_DICTIONARY_H
#define GENERIC_DICTIONARY_DICTIONARY_H

#include <vector>
#include <exception>

#include "AVLTree.h"
#include "KeyValue.h"

template < typename Key, typename Data >
class Dictionary
{
private:
    std::vector< Key > m_keyIndex;
    AVLTree< KeyValue< Key, Data>> m_data;
public:

    Dictionary();                        // Base Constructor
    Dictionary( std::size_t initialSize ); // Overloaded Constructor

    Dictionary( Dictionary& rhs ); // Copy Constructor
    Dictionary( Dictionary&& rhs );       // Move Constructor

    Dictionary& operator=( Dictionary& rhs ); // Copy Assignment
    Dictionary& operator=( Dictionary&& rhs );     // Move Assignment

    void add( Key newKey, Data newData );

    void removeByKey( const Key toRemove );

    void removeByIndex( const std::size_t indexToRemove );

    std::size_t size() const;

    KeyValue< Key, Data >& getByKey( const Key& lookupKey );

    KeyValue< Key, Data >& getByIndex( const std::size_t lookupIndex );

    KeyValue< Key, Data >& operator[]( const std::size_t index );

    void printDictionary( std::ostream& out );

    bool contains( const Key& lookup ) const
    {
        Data temp;
        KeyValue< Key, Data > value( lookup, temp );
        return m_data.search( value );
    }


protected:
    void copy( Dictionary& rhs );
};

template < typename Key, typename Data >
Dictionary< Key, Data >::Dictionary() :
        m_data()
{
    m_keyIndex.reserve( 10 );
}

template < typename Key, typename Data >
Dictionary< Key, Data >::Dictionary( std::size_t initialSize ) : m_data()
{
    m_keyIndex.reserve( initialSize );
}

template < typename Key, typename Data >
Dictionary< Key, Data >::Dictionary( Dictionary& rhs )
{
    copy( rhs );
}

template < typename Key, typename Data >
std::size_t Dictionary< Key, Data >::size() const
{
    if ( m_keyIndex.size() != m_data.numberNodes())
    {
        throw std::out_of_range( "Size of Key Index and Data Tree don't match" );
    }

    return m_keyIndex.size();
}

template < typename Key, typename Data >
Dictionary< Key, Data >::Dictionary( Dictionary&& rhs )
{
//    std::swap( m_keyIndex, rhs.m_keyIndex );
//
//    std::swap( m_data, rhs.m_data );
    copy( rhs );
}

template < typename Key, typename Data >
void Dictionary< Key, Data >::copy( Dictionary& rhs )
{
    std::size_t count = rhs.size();
    m_keyIndex.reserve( count );

    for ( std::size_t i = 0; i < count; ++i )
    {
        KeyValue< Key, Data > copy = ( rhs[ i ] );

        m_keyIndex.push_back( copy.getKey());
        m_data.insert( copy );
    }
}

template < typename Key, typename Data >
Dictionary< Key, Data >& Dictionary< Key, Data >::operator=( Dictionary& rhs )
{
    if ( this != &rhs )
    {
        copy( rhs );
    }

    return *this;
}

template < typename Key, typename Data >
Dictionary< Key, Data >& Dictionary< Key, Data >::operator=( Dictionary&& rhs )
{
    copy( rhs );

    return *this;
}

template < typename Key, typename Data >
void Dictionary< Key, Data >::add( Key newKey, Data newData )
{
//    if (newKey == nullptr)
//    {
//        throw std::out_of_range("Null is not a valid key");
//    }

    KeyValue< Key, Data > value( newKey, newData );

    m_data.insert( value );

    m_keyIndex.push_back( newKey );
}

template < typename Key, typename Data >
void Dictionary< Key, Data >::removeByKey( const Key toRemove )
{

//    if (toRemove == nullptr)
//    {
//        throw std::out_of_range("Null is not a valid key");
//    }

    Data temp;
    KeyValue< Key, Data > value( toRemove, temp );

    m_data.remove( value );

    for ( size_t i = 0; i < m_keyIndex.size(); ++i )
    {
        if ( toRemove == m_keyIndex[ i ] )
        {
            m_keyIndex.erase( m_keyIndex.begin() + i );
            return;
        }
    }


}

template < typename Key, typename Data >
void Dictionary< Key, Data >::removeByIndex( const std::size_t indexToRemove )
{
    if ( indexToRemove >= m_keyIndex.size())
    {
        throw std::out_of_range( "IndexToRemove is outside of the valid range" );
    }

    removeByKey( m_keyIndex[ indexToRemove ] );
}

template < typename Key, typename Data >
KeyValue< Key, Data >& Dictionary< Key, Data >::getByKey( const Key& lookupKey )
{
//    if (lookupKey == nullptr)
//    {
//        throw std::out_of_range("Null pointer not allowed as a Key");
//    }
    Data data;
    KeyValue< Key, Data > lookup( lookupKey, data );

    return m_data.get( lookup );
}

template < typename Key, typename Data >
KeyValue< Key, Data >& Dictionary< Key, Data >::getByIndex( const std::size_t lookupIndex )
{
    if ( lookupIndex >= m_keyIndex.size())
    {
        throw std::out_of_range( "lookupIndex is outside of the valid range" );
    }

    return getByKey( m_keyIndex[ lookupIndex ] );
}

template < typename Key, typename Data >
KeyValue< Key, Data >& Dictionary< Key, Data >::operator[]( const std::size_t index )
{
    if ( index >= m_keyIndex.size())
    {
        throw std::out_of_range( "index is outside of the valid range" );
    }

    return getByKey( m_keyIndex[ index ] );
}

template < typename Key, typename Data >
void Dictionary< Key, Data >::printDictionary( std::ostream& out )
{

    for ( auto& key : m_keyIndex )
    {
        getByKey( key ).display( out );
    }

}


#endif //GENERIC_DICTIONARY_DICTIONARY_H
