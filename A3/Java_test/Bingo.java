abstract class myAbstractClass {
    public abstract String bingoString();
}

class Bingo<T extends myAbstractClass> {

    public void dingo(T t) {
        System.out.println(t.bingoString());
    }

    public static void main(String[] args) {

    }
}
