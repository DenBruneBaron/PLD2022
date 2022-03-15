public class A {
    void f() { System.out.println("A"); }
    void g () { this.f ( ) ; }
}

class B extends A {
    void f ( ) { System.out.println("B");}
}
public class Foo {
    public static void main (String [] args ) {
B b = new B( ) ;
    b.g () ; }
}
