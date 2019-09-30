import java.util.concurrent.atomic.AtomicBoolean;

class SearcherThread<T> extends Thread
{
    private T needle;
    private T[] haystack;
    private int start, end;
    private int result;
    private AtomicBoolean isFound;

    public SearcherThread(T needle, T[] haystack, int start, int end, AtomicBoolean isFound)
    {
        this.needle = needle;
        this.haystack = haystack;
        this.start = start;
        this.end = end;
        this.result = -1;
        this.isFound = isFound;
    }

    public int getResult()
    {
        return this.result;
    }

    @Override
    public void run()
    {
        for (int i=start; i<end &&!Thread.currentThread().isInterrupted() && !isFound.get(); ++i) {
            if (haystack[i].equals(needle)) {
                result = i;
                isFound.set(true);
            }
        }
    }
}