import java.util.ArrayList;
import java.util.concurrent.atomic.AtomicBoolean;


public class Searcher {
    static <T> int search(T needle, T[] haystack, int numThreads) throws InterruptedException {

        AtomicBoolean isFound = new AtomicBoolean(false);

        ArrayList<SearcherThread<T>> searchers = new ArrayList<>();
        int numItemsPerThread = haystack.length / numThreads;
        int extraItems = haystack.length - numItemsPerThread * numThreads;

        for (int i = 0, start = 0; i < numThreads; ++i) {
            int numItems = (i < extraItems) ? (numItemsPerThread + 1) : numItemsPerThread;
            searchers.add(new SearcherThread<T>(needle, haystack, start, start + numItems, isFound));
            start += numItems;
        }
        for (SearcherThread<T> searcher : searchers)
            searcher.start();

        for (SearcherThread<T> searcher : searchers)
            searcher.join();
        for (SearcherThread<T> searcher : searchers) {
            int searchResult = searcher.getResult();
            if (searchResult > -1)
                return searchResult;
        }

        return -1; //not found in any of the threads

    }

    public static void main(String[] args) throws InterruptedException {
        int numThreads = 4;

        int numItems = 10000;
        Integer[] haystack = new Integer[numItems];
        int domainSize = 1000;
        for (int i = 0; i < numItems; ++i)
            haystack[i] = (int) (Math.random() * domainSize);
        int needle = 10;

        long startTime = System.currentTimeMillis();

        int index = Searcher.search(needle, haystack, numThreads);

        long stopTime = System.currentTimeMillis();
        long elapsedTime = stopTime - startTime;

        System.out.println("Time to find the index of the needle found first over all search threads: " + elapsedTime + " ms");
        System.out.println("Needle is found at index: " + index);
    }
}