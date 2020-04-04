import java.io.IOException;

public class Grader {
	
	public int n = 7;
	public int q = 5;

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

	}
	
	public void testCase1() {
		n = 2;
		q = 1;
		addRoad(0, 1);
		buildFarms();
		notifyFJ(0, 0);
		notifyFJ(0, 1);
		notifyFJ(1, 1);
	}
	
	public void testCase2() {
		n = 7;
		q = 4;
		addRoad(0, 2);
		addRoad(1, 0);
		addRoad(4, 2);
		addRoad(2, 5);
		addRoad(3, 6);
		addRoad(3, 0);
		buildFarms();
		notifyFJ(0, 3);
		notifyFJ(5, 6);
		notifyFJ(1, 4);
		notifyFJ(2, 6);
	}
	
	public void addRoad(int a, int b) {
	    // Fill in code here
	}
	        
  	public void buildFarms(){
  		// Fill in code here
	}
	  	
	public void notifyFJ(int a, int b){
	    // Fill in code here
	}
	
	public int getN() {
		return n;
	}
	
	public int getQ() {
		return q;
	}
	
	public void setFarmLocation(int id, int x, int y) {
		System.out.printf("Farm %d placed at (%d, %d)\n", id, x, y);
	}
	
	public void addBox(int x1, int y1, int x2, int y2) {
		System.out.printf("Box placed with endpoints (%d, %d), (%d, %d)\n", x1, y1, x2, y2);
	}

}
