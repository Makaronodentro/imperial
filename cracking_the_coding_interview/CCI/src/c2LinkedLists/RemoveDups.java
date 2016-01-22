package c2LinkedLists;
import java.util.HashSet;

/**
 * Created by Makaronodentro on 21/01/2016.
 */
public class RemoveDups {

    public static void main(String[] args){

    }

    public void deleteDups<T>(LinkedListNode<T> n){
        HashSet<Integer> set = new HashSet<Integer>();
        LinkedListNode<T> previous = null;

        while(n != null) {
            if(set.contains(n.data)){
                previous.next = n.next;
            }
            else{
                set.add(n.data);
                previous = n;
            }
            n = n.next;
        }
    }
}
