import java.io.*;
import java.util.*;

/**
 * Class invariant: This code for a binary tree satisfies the
 * binary search tree storage rule.
 * CSSSKL 143
 * @author (your name) 
 * @version (a version number or a date)
/**
 */

 public class CharTree {
     
     /*Inner class Node, 2 references(pointers), one data element
      * The only reason this inner class is static is that it is used in 
      * the static methods insertInSubtree , isInSubtree , and 
      * showElementsInSubtree. This class should have more methods. 
      * This is just a sample of possible methods.
      */
     private static class TreeNode {
    private char data;
    public TreeNode leftLink;
    public TreeNode rightLink;
        // Declare private data type char
        // Declare 2 links, rightLink & leftLink of type TreeNode
       
         
         // Parametrized constructor to build a node
         public TreeNode(char newData, TreeNode newLeftLink, TreeNode newRightLink) {
            data = newData;
            leftLink = newLeftLink;
            rightLink = newRightLink;
             
         }
     }           //End of IntTreeNode inner class
     
     // The first node of the tree, called root
     private TreeNode root;
     
     // Default constructor to build the CharTree
     public CharTree( ) {
         root = null;
     }
     
     // Utility methods for CharTree:
     public void add(char item) {
         root = insertInSubtree(item, root);
     }
 
     
     public boolean contains(char item) {
         return isInSubtree(item, root);
     }
     
     public void showElements( ) {
         showElementsInSubtree(root);
     }
     
     /**
     Returns the root node of a tree that is the tree with root node
     subTreeRoot, but with a new node added that contains item.
     */
     private static TreeNode insertInSubtree(char item, TreeNode subTreeRoot) {
         if (subTreeRoot == null)
            return new TreeNode(item, null, null);
         else if (item < subTreeRoot.data) {
             subTreeRoot.leftLink = insertInSubtree(item, subTreeRoot.leftLink);
                return subTreeRoot;
         }
         else {         //item >= subTreeRoot.data
               subTreeRoot.rightLink = insertInSubtree(item, subTreeRoot.rightLink);
                 return subTreeRoot;
         }
     }
     
     private static boolean isInSubtree(char item, TreeNode subTreeRoot) {
         // base case: is subTreeRoot null?    then return false
        if(subTreeRoot == null){
            return false;
        }
        // else if subTreeRoot.data == item   what would you return?
        if(subTreeRoot.data == item){
            return true;
        }
        // else item < subTreeRoot.data
            // recursive call
        if(item < subTreeRoot.data){
            return isInSubtree(item, subTreeRoot.leftLink);
        }else{
            return isInSubtree(item,subTreeRoot.rightLink);
        }
         //else         // item >= link.data
            // recursive call
        }
        
     private static void showElementsInSubtree(TreeNode subTreeRoot) { //Uses inorder traversal.
         if (subTreeRoot != null) {
             
             showElementsInSubtree(subTreeRoot.leftLink);
             System.out.print(subTreeRoot.data + " ");
             showElementsInSubtree(subTreeRoot.rightLink);
         }                    //else do nothing. Empty tree has nothing to display.
     }

    public static void main(String[] args) {
        CharTree tree = new CharTree();
        tree.add('c');
        tree.add('a');
        tree.add('t');
        tree.add('s');
        showElementsInSubtree(tree.root);
        
    }
 }
