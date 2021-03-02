package JavaHomeworks.DataFrameJava;

import java.util.*;

public class SparseSeries extends Series {
    public List<COOValue> cooValues;
    public String hide;

    public SparseSeries(String name, String type) {
        super(name, type);
        cooValues = new ArrayList<>();
    }

    public String getValues(int i) {
        return cooValues.get(i).print();
    }

    public String getName() {
        return name;
    }

    public int length() {
        return cooValues.size();
    }

    public SparseSeries(Series series, String hide) {
        super(series.name, series.type);
        int counter = 0;
        cooValues = new ArrayList<>();
        this.hide = hide;
        for (String values : series.getValues()) {
            if (!values.equals(hide)) {
                cooValues.add(new COOValue(counter, series.getValues(counter)));
            }
            counter++;
        }
    }
}
