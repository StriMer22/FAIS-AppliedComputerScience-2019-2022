package JavaHome.DataFrameJava;

import java.util.ArrayList;

public class Series {
    public String name;
    public String type;
    ArrayList<String> values;

    public Series(String name, String type){
        this.name = name;
        this.type = type;
        this.values = new ArrayList<>();
    }

    public Series(String name, String type, ArrayList<String> list){
        this.name = name;
        this.type = type;
        this.values = list;
    }

    public Series(String name, String type, String s) {
        this.name = name;
        this.type = type;
        values = new ArrayList<>();
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setType(String type){
        this.type = type;
    }

    public String getValues(int element){
        return values.get(element);
    }

    public String getType() {
        return type;
    }

    public ArrayList<String> getValues() {
        return values;
    }

    public int length() {
        return this.values.size();
    }

    public Series(SparseSeries sparseSeries){
        this.name = sparseSeries.getName();
        this.type = sparseSeries.getType();

        values = new ArrayList<>();
        for (int i = 0; i <= sparseSeries.cooValues.get(sparseSeries.length()-1).getIndex(); i++){
            for (COOValue cooValue : sparseSeries.cooValues) {
                if (cooValue.getIndex() == i){
                    values.add(cooValue.getValue());
                    i++;
                }
            }
            if (i < sparseSeries.cooValues.get(sparseSeries.length() -1).getIndex()){
                values.add(sparseSeries.hide);
            }
        }
    }


}
