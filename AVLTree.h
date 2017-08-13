// Created by Aaron Fine for CS3 at Utah State University

#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include <algorithm>
#include <ostream>
#include <fstream>
#include <iomanip>
#include <sstream>

template < typename T >
class AVLTree
{
public:
    AVLTree() :
            m_rootNode( nullptr )
    {
        // Empty
    }

    ~AVLTree();

    // Inserts a value into the tree, does not allow duplicates.
    // If the value is already in the tree, false is returned, true otherwise.
    void insert( T value );

    // Deletes a value from the tree. Needs to handle trying to delete a value that is not in the tree
    void remove( T value );

    // Tests to see if a value exists in the tree
    bool search( T value ) const;

    // Looks for the searchValue, and return the matched value in the tree
    T& get( const T& searchValue );

    // Looks for the searchValue, and return the matched value in the tree for modification
    T& access( T& searchValue );

    // Returns a count of all nodes in the tree
    std::size_t numberNodes() const;

    // Returns a count of all the leaf nodes in the tree
    std::size_t numberLeafNodes() const;

    // Returns the height of the tree
    std::size_t height() const;

    // Displays the contents of the tree in sorted order
    void display( std::ostream& ) const;

    // Creates a file that can be read by GraphViz for display
    void createDotFile( std::string filename );

    // Displays the contents of the tree in sorted order
    friend std::ostream& operator<<( std::ostream& output, const AVLTree& tree )
    {
        std::stringstream ss;
        tree.display( ss );
        output << ss.str();
        return output;
    }

private:
    class TreeNode
    {
    public:
        TreeNode( T newData )
                :
                data( newData ),
                leftBranch( nullptr ),
                rightBranch( nullptr ),
                height( 0 )
        {
            // Empty
        }

        T data;
        TreeNode* leftBranch;
        TreeNode* rightBranch;
        std::size_t height;
    };

    TreeNode* m_rootNode;

    std::size_t m_nullcount;

    const int ALLOWED_IMBALANCE = 1;

    // Inserts a value into the tree, does not allow duplicates.
    // If the value is already in the tree, false is returned, true otherwise.
    void insert( TreeNode*& currentNode, TreeNode* newNode, std::size_t previousHeight );

    // Deletes a value from the tree.
    // Needs to handle trying to delete a value that is not in the tree
    void remove( TreeNode*& currentNode, T valueToRemove );

    // Tests to see if a value exists in the tree
    static bool search( const TreeNode* currentNode, const T& value );

    //
    T& get( TreeNode* currentNode, const T& searchValue );

    T& access( TreeNode* currentNode, T& searchValue );

    // Returns a count of all nodes in the tree
    std::size_t numberNodes( const TreeNode* currentNode ) const;

    // Returns a count of all the leaf nodes in the tree
    std::size_t numberLeafNodes( const TreeNode* currentNode ) const;

    // Returns the height of the tree
    std::size_t height( const TreeNode* currentNode ) const;

    // Displays the contents of the tree in sorted order
    void display( TreeNode* currentNode, std::ostream& ) const;

    // Recursively deletes all children nodes
    void deleteTree( TreeNode* currentNode );

    // Recursivley sets the height of all children nodes
    void setHeights( TreeNode* currentNode, std::size_t height );

    // Helper function for printDotFile. Tracks and prints "null" points
    void printNull( const T& key, std::ostream& stream ) const;

    // Helper function for printDotFile. Recursivley generates file data for all children
    void printChildren( const TreeNode* node, std::ostream& stream );

    // Generates a GraphViz compatible file from the source "tree" node down to all of its children
    void printDotFile( const TreeNode* tree, std::ostream& stream );

    // Compares heights of the left and right branches of currentNode to determine which, if any, balancing
    // method to perform on the tree
    void balance( TreeNode*& currentNode );

    // Standard AVL Left Left rotation
    void rotateLeft( TreeNode*& baseNode );

    // Standard AVL Right Right rotation
    void rotateRight( TreeNode*& baseNode );

    // Standard AVL Left Right rotation
    void rotateDoubleLeft( TreeNode*& baseNode );

    // Standard AVL Right Left rotation
    void rotateDoubleRight( TreeNode*& baseNode );
};

template < typename T >
AVLTree< T >::~AVLTree()
{
    deleteTree( m_rootNode );
}

template < typename T >
void AVLTree< T >::deleteTree( TreeNode* currentNode )
{
    // Code from book:

    if ( currentNode == nullptr ) return;

    deleteTree( currentNode->leftBranch );
    deleteTree( currentNode->rightBranch );

    delete currentNode;
}

template < typename T >
void AVLTree< T >::insert( T value )
{
    TreeNode* input = new TreeNode( value );

    insert( m_rootNode, input, 0 );
}

template < typename T >
void AVLTree< T >::remove( T valueToRemove )
{
    remove( m_rootNode, valueToRemove );
}

template < typename T >
bool AVLTree< T >::search( const T value ) const
{
    return search( m_rootNode, value );
}

template < typename T >
std::size_t AVLTree< T >::numberNodes() const
{
    return numberNodes( m_rootNode );
}

template < typename T >
std::size_t AVLTree< T >::numberLeafNodes() const
{
    return numberLeafNodes( m_rootNode );
}

template < typename T >
std::size_t AVLTree< T >::height() const
{
    return height( m_rootNode );
}

template < typename T >
void AVLTree< T >::display( std::ostream& output ) const
{
    if ( m_rootNode == nullptr )
    {
        output << "Root Node is NULL";
        return;
    }
    display( m_rootNode, output );
}

template < typename T >
void AVLTree< T >::insert( TreeNode*& currentNode, TreeNode* newNode, std::size_t previousHeight )
{
    if ( currentNode == nullptr )
    {
        if ( currentNode != m_rootNode )
        {
            newNode->height = ++previousHeight;
        }
        currentNode = newNode;
        // return true;
    } else if ( newNode->data > currentNode->data )
    {
        insert( currentNode->rightBranch, newNode, currentNode->height );
    } else if ( newNode->data < currentNode->data )
    {
        insert( currentNode->leftBranch, newNode, currentNode->height );
    } else
    {
        throw std::domain_error("Value already exists");
    }

    balance( currentNode );
}

template < typename T >
void AVLTree< T >::remove( TreeNode*& currentNode, T valueToRemove )
{

    if ( currentNode == nullptr )
    {
        // nothing in the tree matches the value we are removing
        throw std::domain_error("Value to remove doesn't exist");
    }

    // Recursivley search the tree for the value
    if ( valueToRemove < currentNode->data )
    {
        remove( currentNode->leftBranch, valueToRemove );
    } else if ( valueToRemove > currentNode->data )
    {
        remove( currentNode->rightBranch, valueToRemove );
    } else
    {
        //  valueToRemove == currentNode->data MUST be true thus
        // We found our tree node to remove!

        TreeNode* deleteMe = currentNode;

        if ( currentNode->leftBranch == nullptr )
        {
            // There is no left branch, so move the right side up to our current spot in the tree
            currentNode = currentNode->rightBranch;
        } else if ( currentNode->rightBranch == nullptr )
        {
            // There is no right branch, so move the right side up to our current spot in the tree
            currentNode = currentNode->leftBranch;
        } else
        {
            // We have two branches so we have to spice the left onto the right then move the
            // right up to our current spot in the tree

            TreeNode* leftMost = currentNode->rightBranch;
            // To find the correct place to splice the left branch onto we start at the right side

            while ( leftMost->leftBranch != nullptr )
            {
                leftMost = leftMost->leftBranch;
            }

            // LeftMost now has the actual left most element of our currentNodes RightBranch tree
            // Splice the right tree onto the leftmost element of the right branch
            leftMost->leftBranch = currentNode->leftBranch;
            currentNode = currentNode->rightBranch;
        }

        setHeights( currentNode, deleteMe->height );
        delete deleteMe;
    }
}

template < typename T >
bool AVLTree< T >::search( const TreeNode* currentNode, const T& value )
{
    // Code from the book:
    while ( currentNode != nullptr )
    {
        if ( currentNode->data == value )
        {
            return true;
        } else if ( value < currentNode->data )
        {
            currentNode = currentNode->leftBranch;
        } else
        {
            currentNode = currentNode->rightBranch;
        }
    }

    return false;
}

template < typename T >
std::size_t AVLTree< T >::numberNodes( const TreeNode* currentNode ) const
{
    if ( currentNode == nullptr )
    {
        return 0;
    }

    return 1 + numberNodes( currentNode->leftBranch ) + numberNodes( currentNode->rightBranch );
}

template < typename T >
std::size_t AVLTree< T >::numberLeafNodes( const TreeNode* currentNode ) const
{
    if ( currentNode == nullptr )
    {
        return 0;
    }

    if ( currentNode->leftBranch == nullptr && currentNode->rightBranch == nullptr )
    {
        return 1;
    } else
    {
        return 0
               + numberLeafNodes( currentNode->leftBranch )
               + numberLeafNodes( currentNode->rightBranch );
    }
}

template < typename T >
std::size_t AVLTree< T >::height( const TreeNode* currentNode ) const
{
    if ( currentNode == nullptr )
    {
        return 0;
    }

    return 1 + std::max( height( currentNode->leftBranch ), height( currentNode->rightBranch ));
}

template < typename T >
void AVLTree< T >::display( TreeNode* currentNode, std::ostream& output ) const
{
    if ( currentNode != nullptr )
    {
        display( currentNode->rightBranch, output );

        output << std::setw( static_cast<int>(currentNode->height * 4)) << currentNode->data << std::endl;

        display( currentNode->leftBranch, output );
    }

}

template < typename T >
void AVLTree< T >::setHeights( TreeNode* currentNode, std::size_t height )
{
    if ( currentNode == nullptr )
    {
        return;
    }

    currentNode->height = height++;
    setHeights( currentNode->leftBranch, height );
    setHeights( currentNode->rightBranch, height );

}

// Code adapted from http://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz
template < typename T >
void AVLTree< T >::printNull( const T& key, std::ostream& stream ) const
{

    stream << "    null" << m_nullcount << " [shape=point];\n";
    stream << "    " << key << " -> null" << m_nullcount << ";\n";
}

// Code adapted from http://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz
template < typename T >
void AVLTree< T >::printChildren( const TreeNode* node, std::ostream& stream )
{

    if ( node->leftBranch )
    {
        stream << "    " << node->data << " -> " << node->leftBranch->data << ";\n";
        printChildren( node->leftBranch, stream );
    } else
    {
        ++m_nullcount;
        printNull( node->data, stream );
    }

    if ( node->rightBranch )
    {
        stream << "    " << node->data << " -> " << node->rightBranch->data << ";\n";
        printChildren( node->rightBranch, stream );
    } else
    {
        ++m_nullcount;
        printNull( node->data, stream );
    }
}

// Code adapted from http://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz
template < typename T >
void AVLTree< T >::printDotFile( const TreeNode* tree, std::ostream& stream )
{
    stream << "digraph BST {\n";
    stream << "    node [fontname=\"Arial\"];\n";

    if ( !tree )
    {
        stream << "\n";
    } else if ( !tree->rightBranch && !tree->leftBranch )
    {
        stream << "    " << tree->data << ";\n";
    } else
    {
        printChildren( tree, stream );
    }
    stream << "}\n";
}

template < typename T >
void AVLTree< T >::createDotFile( std::string filename )
{
    std::ofstream fout( filename );
    m_nullcount = 0;
    printDotFile( m_rootNode, fout );

    fout.close();
}

template < typename T >
void AVLTree< T >::rotateLeft( TreeNode*& baseNode )
{
    // Left Left rotation
    /*Starting Config
     *       5 <- Base Node
     *     4   D
     *   3   C
     * A   B
     *
     * Ending Config
     *       4
     *   3       5
     * A   B   C   D
     */
    // if (baseNode->height < 2) return;

    auto oldBase = baseNode;
    auto middle = baseNode->leftBranch;
    auto cappa = middle->rightBranch;

    baseNode = middle;
    baseNode->rightBranch = oldBase;
    oldBase->leftBranch = cappa;
    //baseNode->height = oldBase->height;

}

template < typename T >
void AVLTree< T >::rotateRight( TreeNode*& baseNode )
{
// Left Left rotation
    /*Starting Config
     *   3 <- Base Node
     * A   4
     *   B   5
     *     C   D
     *
     * Ending Config
     *       4
     *   3       5
     * A   B   C   D
     */
    //if (baseNode->height < 2) return;

    auto oldBase = baseNode;
    auto middle = baseNode->rightBranch;
    auto beta = middle->leftBranch;

    baseNode = middle;
    baseNode->leftBranch = oldBase;
    oldBase->rightBranch = beta;
    //baseNode->height = oldBase->height;

}

template < typename T >
void AVLTree< T >::rotateDoubleLeft( TreeNode*& baseNode )
{
// Left Right rotation
    /*Starting Config
     *     5 <- Base Node
     *   3   D
     * A   4
     *   B   C
     *
     * Ending Config
     *       4
     *   3       5
     * A   B   C   D
     */
    //if (baseNode->height < 2) return;

    auto oldBase = baseNode;
    auto middle = baseNode->leftBranch;
    auto bottom = baseNode->leftBranch->rightBranch;
    auto beta = bottom->leftBranch;
    auto cappa = bottom->rightBranch;

    baseNode = bottom;
    baseNode->leftBranch = middle;
    baseNode->rightBranch = oldBase;

    middle->rightBranch = beta;
    oldBase->leftBranch = cappa;
}

template < typename T >
void AVLTree< T >::rotateDoubleRight( TreeNode*& baseNode )
{
// Right Left rotation
    /*Starting Config
     *     3 <- Base Node
     *   A   5
     *     4   D
     *   B   C
     *
     * Ending Config
     *       4
     *   3       5
     * A   B   C   D
     */
    //if (baseNode->height < 2) return;

    auto oldBase = baseNode;
    auto middle = baseNode->rightBranch;
    auto bottom = baseNode->rightBranch->leftBranch;
    auto beta = bottom->leftBranch;
    auto cappa = bottom->rightBranch;

    baseNode = bottom;
    baseNode->leftBranch = oldBase;
    baseNode->rightBranch = middle;

    middle->leftBranch = cappa;
    oldBase->rightBranch = beta;
}

template < typename T >
void AVLTree< T >::balance( TreeNode*& currentNode )
{
//****************************************************************************************************
//******************************* Example from book **************************************************
//    if (currentNode == nullptr) return;
//
//    if (height(currentNode->leftBranch) - height(currentNode->rightBranch) > ALLOWED_IMBALANCE)
//    {
//        if (height(currentNode->leftBranch->leftBranch) >= height(currentNode->leftBranch->rightBranch))
//        {
//            rotateLeft(currentNode);
//        } else
//        {
//            rotateDoubleLeft(currentNode);
//        }
//    } else if (height(currentNode->rightBranch) - height(currentNode->leftBranch) > ALLOWED_IMBALANCE)
//    {
//        if (height(currentNode->rightBranch->rightBranch) >= height(currentNode->rightBranch->leftBranch))
//        {
//            rotateRight(currentNode);
//        } else
//        {
//            rotateDoubleRight(currentNode);
//        }
//    }
//
//    currentNode->height = std::max(height(currentNode->leftBranch), height(currentNode->rightBranch)) + 1;
//
//****************************************************************************************************

    std::size_t currentHeight = currentNode->height;

    std::size_t leftHeight = 0;
    std::size_t rightHeight = 0;
    std::size_t leftLeftHeight = 0;
    std::size_t leftRightHeight = 0;
    std::size_t rightRightHeight = 0;
    std::size_t rightLeftHeight = 0;

    // grab heights if and only if the children are not null. Heights are zero otherwise.
    if ( currentNode->leftBranch != nullptr )
    {
        leftHeight = height( currentNode->leftBranch );
        if ( currentNode->leftBranch->leftBranch != nullptr )
        {
            leftLeftHeight = height( currentNode->leftBranch->leftBranch );
        }
        if ( currentNode->leftBranch->rightBranch != nullptr )
        {
            leftRightHeight = height( currentNode->leftBranch->rightBranch );
        }
    }

    if ( currentNode->rightBranch != nullptr )
    {
        rightHeight = height( currentNode->rightBranch );
        if ( currentNode->rightBranch->rightBranch != nullptr )
        {
            rightRightHeight = height( currentNode->rightBranch->rightBranch );
        }

        if ( currentNode->rightBranch->leftBranch != nullptr )
        {
            rightLeftHeight = height( currentNode->rightBranch->leftBranch );
        }
    }

    // Compare heights. NOTE: size_t values cannot be negative so we have to
    // check to see that one is greater than the other before subtracting
    if ( leftHeight > rightHeight && leftHeight - rightHeight > ALLOWED_IMBALANCE )
    {
        // Left is bigger than right
        if ( leftLeftHeight > leftRightHeight )
        {
            // Left Left Rotation
            rotateLeft( currentNode );
        } else
        {
            // Left Right Rotation
            rotateDoubleLeft( currentNode );
        }

    } else if ( rightHeight > leftHeight && rightHeight - leftHeight > ALLOWED_IMBALANCE )
    {
        // Right is bigger than left
        if ( rightRightHeight > rightLeftHeight )
        {
            // Right Right Rotation
            rotateRight( currentNode );
        } else
        {
            // Right Left Rotation
            rotateDoubleRight( currentNode );
        }

    } else
    {
        // No rotations to do
        return;
    }

    // We have done a rotation. Now we need to fix the heights.
    setHeights( currentNode, currentHeight );
}

template < typename T >
T& AVLTree< T >::get( const T& searchValue )
{
    return get( m_rootNode, searchValue );
}

template < typename T >
T& AVLTree< T >::get( AVLTree::TreeNode* currentNode, const T& searchValue )
{
    while ( currentNode != nullptr )
    {
        if ( currentNode->data == searchValue )
        {
            return currentNode->data;
        } else if ( searchValue < currentNode->data )
        {
            currentNode = currentNode->leftBranch;
        } else
        {
            currentNode = currentNode->rightBranch;
        }
    }

   throw std::domain_error("Search value not in tree");
}

template < typename T >
T& AVLTree< T >::access( T& searchValue )
{
    return access(m_rootNode, searchValue);
}

template < typename T >
T& AVLTree< T >::access( TreeNode* currentNode, T& searchValue )
{
    while ( currentNode != nullptr )
    {
        if ( currentNode->data == searchValue )
        {
            return currentNode->data;
        } else if ( searchValue < currentNode->data )
        {
            currentNode = currentNode->leftBranch;
        } else
        {
            currentNode = currentNode->rightBranch;
        }
    }

    throw std::domain_error("Search value not in tree");
}

#endif // !_AVL_TREE_H
