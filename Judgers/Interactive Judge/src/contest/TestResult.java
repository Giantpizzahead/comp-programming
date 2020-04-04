package contest;

public class TestResult {
    public double score;
    public int ms, mem;
    public String comment;

    public TestResult(double score, int ms, int mem, String comment) {
        this.score = score;
        this.ms = ms;
        this.mem = mem;
        this.comment = comment;
    }

    @Override
    public String toString() {
        return "(" + score + ", " + ms + "ms, " + comment + ")";
    }
}
