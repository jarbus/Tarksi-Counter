import java.math.BigInteger;
import java.util.List;
import java.util.LinkedList;

public class TarskisWorld 
{

	final static BigInteger TWO = new BigInteger("2");
	final static BigInteger THREE = new BigInteger("3");

	//taken from https://stackoverflow.com/questions/2201113/combinatoric-n-choose-r-in-java-math
	// code from user polygenelubricants on stack overflow
	static BigInteger binomial(final int N, final int K) 
	{
	    BigInteger ret = BigInteger.ONE;
	    for (int k = 0; k < K; k++) 
		{
	        ret = ret.multiply(BigInteger.valueOf(N-k)).divide(BigInteger.valueOf(k+1));
	    }
	    return ret;
	}

	private static BigInteger num_world_small(int n, int location_count) 
	{	
		return binomial(location_count,n).multiply(TWO.pow(n));
	}

	/**
	 * looks at all the places it could place a large object if l > 1 and returns
	 * the sum of all the different possibilities
	 */
	// c: current number of large object left to be places
	// l: number of small objects we expect to add ultimately
	private static BigInteger num_world_with_large(int l, int s, List<List<Integer>> world) 
	{
		if(l==0) 
		{
			int open_spaces = 64;
			//subtract away occupied space using world info
			return num_world_small(s,open_spaces);
		}

		BigInteger count = new BigInteger("0");
		//brute force places we can put a large object
		for(int x = 0; x < 8; x++) 
		{
			for(int y = 0; y < 8; y++) 
			{
				//try adding a large object at x,y if it is valid
				if(false) continue;
				count.add(num_world_with_large(l,s,world));

			}
		}

		return count;
	}

	public static void main(String[] args) 
	{

		BigInteger count = new BigInteger("0");

		for(int n = 0; n <= 12; n++) {
			for(int l = 0; l <= n; l++) {

				BigInteger world_count = num_world_with_large(l, n-l, new LinkedList<List<Integer>>());

				BigInteger n_plus_one = new BigInteger(new Integer(n+1).toString());

				// factor = 3^n x (n+1)^6
				BigInteger factor = THREE.pow(n).multiply(n_plus_one.pow(6));

				count = count.add(world_count.multiply(factor));

			}
		}
		//System.out.println(count);
		System.out.println(count);
	}


}