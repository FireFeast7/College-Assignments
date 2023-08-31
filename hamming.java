import java.util.*;
public class hamming {
	public static int calculate_r(int m) {
		int r = 0;
		while(Math.pow(2,r)<=m+r+1) {
			r++;
		}
		return r;
	}
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.print("Enter the length of the bit");
		int len = sc.nextInt();
		int r = calculate_r(len);
		System.out.print(r);
		int min = Integer.MIN_VALUE;
		ArrayList<Integer> signal = new ArrayList<Integer>(len+r);
		int k = 0;
		for(int i = 1;i<=len+r;i++) {
			if(Math.pow(2, k) == i) {
				signal.add(min);
				k++;
			}
			else {
				signal.add(0);
			}
		}
		for (int i = len + r - 1; i >= 0; i--) {
		    if (signal.get(i) != min) {
		        signal.remove(i);
		        signal.add(i, sc.nextInt());
		    }
		}
		for (double b = 0; b< r; b++) {
		    double i = Math.pow(2, b) - 1;
		    System.out.print(i);
		}
		
		System.out.print(signal);
	}
}
