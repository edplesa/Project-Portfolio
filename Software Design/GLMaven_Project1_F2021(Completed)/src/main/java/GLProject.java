import java.util.ArrayList;
import java.util.Iterator;
public class GLProject {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		//System.out.println("Welcome to project 1");
		
		GenericStack<Integer> stack = new GenericStack<>(10);
		stack.push(11);
		stack.push(12);
		stack.push(13);
		
		
		stack.print();
		
		ArrayList<Integer> list = stack.dumpList();
		
		for (Integer elem: list) {
			System.out.println(elem);
		}
		
	}
}
