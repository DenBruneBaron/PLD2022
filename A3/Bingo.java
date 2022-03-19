class myClass {
    public String bingoString(){
        return "This is bingo string, who dis?";
    }

}

class Bingo<T extends myClass> {

    public void dingo(T t) {
        System.out.println(t.bingoString());
    }

    public static void main(String[] args) {
        Bingo newBingo = new Bingo();
        newBingo.dingo(new myClass());
    }
}
