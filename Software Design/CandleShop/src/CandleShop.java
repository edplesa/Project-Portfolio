import java.util.Scanner;

public class CandleShop {
    public static double discount(double amount) {

        if (amount > 20 && amount < 35) {
            return amount * .95;
        } else if (amount > 35 && amount < 55) {
            return amount * .93;
        } else if (amount > 55 && amount < 100) {
            return amount * .90;
        } else if (amount > 100) {
            return amount * .80;
        }
        return amount;
    }

    public static int burn(Candle c1, Candle c2, Candle c3, int num1, int num2, int num3) {
        return (num1*c1.getTime() + num2*c2.getTime() + num3*c3.getTime());
    }

    public static double totalCost(Candle c1, Candle c2, Candle c3, int t1, int t2, int t3) {
        return ( (t1*c1.getCost()) + (t2*c2.getCost()) + (t3*c3.getCost()) );
    }

    public static void main(String[] args) {
        Scanner scnr = new Scanner(System.in);
        System.out.println("Enter Name for Candles of type 1: ");
        String type1Name = scnr.nextLine();
        System.out.println("Enter Cost for Candles of type 1: ");
        double type1Cost = Double.parseDouble(scnr.nextLine());
        System.out.println("Enter Burn Time for Candles of type 1: ");
        int type1Burn = Integer.parseInt(scnr.nextLine());

        System.out.println("Enter Name for Candles of type 2: ");
        String type2Name = scnr.nextLine();
        System.out.println("Enter Cost for Candles of type 2: ");
        double type2Cost = Double.parseDouble(scnr.nextLine());
        System.out.println("Enter Burn Time for Candles of type 2: ");
        int type2Burn = Integer.parseInt(scnr.nextLine());

        System.out.println("Enter Name for Candles of type 3: ");
        String type3Name = scnr.nextLine();
        System.out.println("Enter Cost for Candles of type 3: ");
        double type3Cost = Double.parseDouble(scnr.nextLine());
        System.out.println("Enter Burn Time for Candles of type 3: ");
        int type3Burn = Integer.parseInt(scnr.nextLine());

        Candle c1 = new Candle(type1Name, 1, type1Cost, type1Burn);
        Candle c2 = new Candle(type2Name, 2, type2Cost, type2Burn);
        Candle c3 = new Candle(type3Name, 3, type3Cost, type3Burn);

        System.out.println("How many candles of type 1 does the customer want to buy: ");
        int numCandles1 = Integer.parseInt(scnr.nextLine());

        System.out.println("How many candles of type 2 does the customer want to buy: ");
        int numCandles2 = Integer.parseInt(scnr.nextLine());

        System.out.println("How many candles of type 3 does the customer want to buy: ");
        int numCandles3 = Integer.parseInt(scnr.nextLine());

        double total = totalCost(c1, c2, c3, numCandles1, numCandles2, numCandles3);

        System.out.println("Total Cost is: $" + total);

        double totalAfterDiscount = discount(total);

        System.out.println("Total Cost after discount is: $" + totalAfterDiscount);

        int totalBurnTime = burn(c1, c2, c3, numCandles1, numCandles2, numCandles3);

        System.out.println("Total burn time is: " + totalBurnTime);

        System.out.println("Total cost per minute (no discount) is: " + total/totalBurnTime);

        System.out.println("Total cost per minute (with discount) is: " + totalAfterDiscount/totalBurnTime );
    }
}
