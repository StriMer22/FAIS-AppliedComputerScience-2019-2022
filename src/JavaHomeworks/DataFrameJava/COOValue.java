package JavaHomeworks.DataFrameJava;

public final class COOValue {
    public final int index;
    public final String value;

    COOValue(int index, String value) {
        this.index = index;
        this.value = value;
    }

    public String print() {
        return "(" + index + "," + value + ")";
    }

    public int getIndex() {
        return index;
    }
    public String getValue() {
        return value;
    }

}
