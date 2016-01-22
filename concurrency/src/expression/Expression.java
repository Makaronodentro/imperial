package expression;

/**
 * The base class for all classes encapsulating arithmetic expressions.
 */
public abstract class Expression {

    /**
     * Evaluates the expression.
     * @return The evaluation result.
     */
    public abstract int value();

    /**
     * Returns the precedence ranking of this expression.
     * @return The precedence ranking of this expression.
     */
    public abstract int precedence();

    /**
     * Returns a textual representation of this expression
     * using minimum brackets.
     * @return A string representing this expression.
     */
    public abstract String toString();

    /**
     * Prints the given expression and its evaluation result
     * to the standard output.
     * @param e The expression to be printed.
     */
    private static void printExpression(Expression e) {
        System.out.println(e + " = " + e.value());
    }

    /**
     * Entry point of the program. Demonstrates the Expression classes.
     * @param args Unused.
     */
    public static void main(String[] args) {
        Expression n2  = new NumberExpression(2),
        Expression n3  = new NumberExpression(3),
        Expression n_1 = new NumberExpression(-1);

        printExpression(n_1);
        /* OUT: -1 = -1 */

        // Expression a1 = new Addition(n2, n_1);
        // printExpression(a1);
        /* OUT: 2 + (-1) = 1 */

        // Expression a2 = new Addition(n_1, n3);
        // printExpression(a2);
        /* OUT: -1 + 3 = 2 */

        // Expression m1 = new Multiplication(n3, a1);
        // printExpression(m1);
        /* OUT: 3 * (2 + (-1)) = 3 */

        // Expression a3 = new Addition(m1, a1);
        // printExpression(a3);
        /* OUT: 3 * (2 + (-1)) + (2 + (-1)) = 4 */

        // Expression a4 = new Addition(a1, m1);
        // printExpression(a4);
        /* OUT: 2 + (-1) + 3 * (2 + (-1)) = 4 */
    }
}
