package JavaHome.DataFrameJava;

import java.util.*;

public class SparseDataFrame extends DataFrame {
    List<SparseSeries> column = new ArrayList<>();
    String hide;

    SparseDataFrame(String[] col1, String[] col2, String hide){
        super(col1,col2);
        for (int i = 0; i < col1.length; i++){
            columns.add(new SparseSeries(col1[i], col2[i]));
        }
        this.hide = hide;
    }

    SparseDataFrame(DataFrame dataFrame, String hide){
        for (Series column : dataFrame.getCol()) {
            column.setType("int");
            this.column.add(new SparseSeries(column, hide));
        }
        this.hide = hide;
    }

    @Override
    public SparseSeries get(String colName) {
        ArrayList<String> colNames = new ArrayList<>();
        for (SparseSeries columns : column) {
            colNames.add(columns.name);
        }
        return column.get(colNames.indexOf(colName));
    }

    public int size() {
        ArrayList<Integer> temp = new ArrayList<>();
        for (SparseSeries col : column) {
            temp.add(col.length());
        }
        return Collections.max(temp);
    }

    // NEED TO REPAIR
    public void printDataFrame() {
        for (SparseSeries sparseSeries : column) {
            System.out.print(sparseSeries.getName() + "\t\t");
        }
        System.out.println();

        for (int i = 0; i < this.size(); i++) {
            for (SparseSeries col : this.column) {
                if (col.length() <= i) {
                    System.out.println();
                } else {
                    System.out.print(col.getValues(i) + "\t\t");
                }
            }
            System.out.println();
        }
    }

    public DataFrame toDense() {
        DataFrame df = new DataFrame();
        for (SparseSeries col : column) {
            df.columns.add(new Series(col));
        }
        for (Series col : df.columns) {
            if (col.length() != df.size()) {
                for (int i = 0; i < df.size() - col.length(); i++) {
                    col.values.add(hide);
                }
            }
        }
        return df;
    }



}

