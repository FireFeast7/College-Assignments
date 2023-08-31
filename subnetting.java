import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class subnetting {
    public static ArrayList<Integer> bits(int cidr) {
        ArrayList<Integer> breakdown = new ArrayList<>();
        while (cidr >= 0) {
            if (cidr >= 8) {
                breakdown.add(8);
                cidr -= 8;
            } else {
                breakdown.add(cidr);
                break;
            }
        }
        while (breakdown.size() < 4) {
            breakdown.add(0);
        }
        return breakdown;
    }
    public static int networkAddress(StringBuilder address, int range, int a) {
        int t = range;
        for (int i = 0; i < range;) {
            if (a >= i && a <= range) {
                return i;
            } else {
                i += (t + 1);
                range += (t + 1);
            }
        }
        return -1;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the IP address: ");
        String ipadd = sc.nextLine();
        ArrayList<Integer> nums = new ArrayList<>();
        System.out.print("Enter the CIDR: ");
        int cidr = sc.nextInt();
        nums = bits(cidr);
        int rembits = 0;
        System.out.println("Bit breakdown: " + bits(cidr));
        StringBuilder subnetmask = new StringBuilder();
        for (int i = 0; i < nums.size(); i++) {
            if (nums.get(i) == 0) {
                subnetmask.append("0.");
            } else if (nums.get(i) != 8) {
                rembits = 8 - nums.get(i);
                int val = 0;
                int pow = 7;
                for (int j = 0; j < nums.get(i); j++) {
                    val = val + (int) Math.pow(2, pow);
                    pow--;
                }
                subnetmask.append(val + ".");
            } else {
                subnetmask.append("255.");
            }
        }
        System.out.println("The Subnet mask is " + subnetmask.toString().substring(0, subnetmask.toString().length() - 1));
        System.out.println();
        String[] elements = ipadd.split("\\.");
//        System.out.println("The remaining bits are : " + rembits);
        int range = 0;
        int pow = 0;
        for (int j = 0; j < rembits; j++) {
            range = range + (int) Math.pow(2, pow);
            pow++;
        }
//        System.out.println("The range is : " + range);
        StringBuilder address = new StringBuilder();
        int a = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums.get(i) == 8) {
                address.append(elements[i] + ".");
            } else {
                a = Integer.parseInt(elements[i]);
                break;
            }
        }
//        System.out.println("The bit to be searched is " + a);
        address.append(networkAddress(address, range, a) + ".");
        for (int i = 0; i < Collections.frequency(nums, 0); i++) {
            address.append("0.");
        }
        String networkAdd = address.toString().substring(0, address.toString().length() - 1);
        System.out.println("The Network Address is : " + networkAdd);
//        System.out.println("The first IP and last IP is " + (networkAddress(address, range, a) + 1) + " " + (networkAddress(address, range, a) + range));
        String[] octets = networkAdd.split("\\.");
        int last_bit = Integer.parseInt(octets[3]);
        if(last_bit == 0){
            octets[3] = "1";
        }
        else{
            octets[3] = Integer.toString(networkAddress(address, range, a) + 1);
        }
        String first_IP = String.join(".", octets);
        System.out.println(first_IP);
        int rem = 0;
        for(int i = 0;i<nums.size();i++){
            if(nums.get(i)!=8 && nums.get(i)!=0){
                rem = i;
                octets[i] =Integer.toString(networkAddress(address, range, a) +range);
                break;
            }
        }
        for(int i = rem+1;i<nums.size()-1;i++){
            octets[i] = "255";
        }
        octets[3] = "254";
        String last_IP = String.join(".", octets);
        System.out.println(last_IP);
        int total_range = range+1;
        int zerosCount = Collections.frequency(nums, 0);
        for (int i = 0; i < zerosCount; i++) {
            total_range *= 256;
        }
        System.out.println("The Total number of client addresses that can be hosted are : "+(total_range-2));
        sc.close();
    }
}