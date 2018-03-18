

import junit.framework.TestCase;
import java.util.concurrent.ThreadLocalRandom;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }


   public void testManualTest()
   {	
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertEquals("http://www.google.com/ should validate", true, urlVal.isValid("http://www.google.com/"));
	   assertEquals("256.256.256.256 should not validate", false, urlVal.isValid("256.256.256.256"));
	   assertEquals("http://www.google.com/test1 should validate", true, urlVal.isValid("http://www.google.com/test1"));
	   assertEquals("http://138.197.198.178:-1 should not validate", false, urlVal.isValid("http://138.197.198.178:-1"));
   }
   
   
   public void testYourFirstPartition() {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertEquals("http://www.google.com should validate", true, urlVal.isValid("http://www.google.com"));
	   assertEquals("3ht://www.google.com should not validate", false, urlVal.isValid("3ht://www.google.com"));
   }
   
   public void testYourSecondPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertEquals("http://www.go.coms should  validate", true, urlVal.isValid("http://www.go.com"));
	   assertEquals("256.256.256.256 should not validate", false, urlVal.isValid("256.256.256.256"));
   }

   public void testYourThirdPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertEquals("http://138.197.198.178:65535 should validate", true, urlVal.isValid("http://138.197.198.178:65535"));
	   assertEquals("http://138.197.198.178:-1 should not validate", false, urlVal.isValid("http://138.197.198.178:-1"));
   }
   
   public void testYourFourthPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertEquals("http://www.google.com/test1 should validate", true, urlVal.isValid("http://www.google.com/test1"));
	   assertEquals("http://www.google.com/../ should not validate", false, urlVal.isValid("http://www.google.com/../"));
   }
   
   public void testYourFifthPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertEquals("http://www.amazon.com/?action=view should validate", true, urlVal.isValid("http://www.amazon.com/?action=view"));
   }
   
   public void testIsValid()
   {
	   	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String url = "";
		boolean expected = true;
		boolean actual;

		for (int i = 1; i < 10; i++) {
			
			// generate random URL
			int randomScheme = ThreadLocalRandom.current().nextInt(0, 8 + 1);
			int randomAuthority = ThreadLocalRandom.current().nextInt(0, 18 + 1);
			int randomPort = ThreadLocalRandom.current().nextInt(0, 6 + 1);
			int randomPath = ThreadLocalRandom.current().nextInt(0, 9 + 1);
			int randomQuery = ThreadLocalRandom.current().nextInt(0, 2 + 1);
			
			url = testUrlScheme[randomScheme].item + testUrlAuthority[randomAuthority].item + testUrlPort[randomPort].item + testPath[randomPath].item + testUrlQuery[randomQuery].item;
			expected = testUrlScheme[randomScheme].valid & testUrlAuthority[randomAuthority].valid & testUrlPort[randomPort].valid & testPath[randomPath].valid & testUrlQuery[randomQuery].valid;
			System.out.println(url);
			
			//assertion
			actual = urlVal.isValid(url);
			assertEquals(url, expected, actual);
			
			// print results
			System.out.println("expected: " + expected);
			System.out.println("actual: " + actual);
			System.out.println("\n");
		}
   }
   
   
   	ResultPair[] testUrlScheme = {
   		   new ResultPair("http://", true),
           new ResultPair("ftp://", true),
           new ResultPair("h3t://", true),
           new ResultPair("3ht://", false),
           new ResultPair("http:/", false),
           new ResultPair("http:", false),
           new ResultPair("http/", false),
           new ResultPair("://", false),
           new ResultPair("", true)};

	ResultPair[] testUrlAuthority = {
		  new ResultPair("www.google.com", true),
          new ResultPair("go.com", true),
          new ResultPair("go.au", true),
          new ResultPair("0.0.0.0", true),
          new ResultPair("255.255.255.255", true),
          new ResultPair("256.256.256.256", false),
          new ResultPair("255.com", true),
          new ResultPair("1.2.3.4.5", false),
          new ResultPair("1.2.3.4.", false),
          new ResultPair("1.2.3", false),
          new ResultPair(".1.2.3.4", false),
          new ResultPair("go.a", false),
          new ResultPair("go.a1a", false),
          new ResultPair("go.cc", true),
          new ResultPair("go.1aa", false),
          new ResultPair("aaa.", false),
          new ResultPair(".aaa", false),
          new ResultPair("aaa", false),
          new ResultPair("", false)
	};
	ResultPair[] testUrlPort = {
		 new ResultPair(":80", true),
         new ResultPair(":65535", true),
         new ResultPair(":0", true),
         new ResultPair("", true),
         new ResultPair(":-1", false),
         new ResultPair(":65636", true),
         new ResultPair(":65a", false)
	};
	ResultPair[] testPath = {
		  new ResultPair("/test1", true),
		  new ResultPair("/t123", true),
		  new ResultPair("/$23", true),
		  new ResultPair("/..", false),
		  new ResultPair("/../", false),
		  new ResultPair("/test1/", true),
		  new ResultPair("", true),
		  new ResultPair("/test1/file", true),
		  new ResultPair("/..//file", false),
		  new ResultPair("/test1//file", false)
	};


	ResultPair[] testUrlQuery = {
	      new ResultPair("?action=view", true),
          new ResultPair("?action=edit&mode=up", true),
          new ResultPair("", true)
	};
   
}
