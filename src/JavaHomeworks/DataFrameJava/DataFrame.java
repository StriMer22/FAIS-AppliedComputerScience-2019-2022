package JavaHomeworks.DataFrameJava;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

public class DataFrame {

    public List<Series> columns = new ArrayList<>();

    DataFrame(String[] columns2, String[] rows) {
        for (int i = 0; i < columns2.length; i++) {
            columns.add(new Series(columns2[i], rows[i]));
        }
    }

//    JavaHomeworks.DataFrameJava.DataFrame(String fileName, String[] types, String header) {
//        for (int i = 0; i < types.length; i++) {
//            columns.add(new JavaHomeworks.DataFrameJava.Series(fileName,types[i],header));
//        }
//    }

    public DataFrame(List<Series> columns) {
        for (Series column : columns) {
            Series series = new Series(column.getName(), column.getType(), (ArrayList<String>) column.getValues().clone());
            this.columns.add(series);
        }
    }

    public DataFrame() {}

    public int size() {
        ArrayList<Integer> temp = new ArrayList<>();
        for (Series col : this.columns) {
            temp.add(col.length());
        }
        return Collections.max(temp);
    }


    public List<Series> getCol(){
        return columns;
    }

//    public int size() {
//        return columns.get(0).values.size();
//    }

    DataFrame addColumn(String columnName, String dataType, boolean inPlace) {
        if (columns == null) {
            columns = new ArrayList<>();
        }
        Series newSeries = new Series(columnName, dataType, new ArrayList<>());
        if (inPlace) {
            columns.add(newSeries);
            return this;
        } else {
            List<Series> seriesCopy = new ArrayList<>(columns);
            seriesCopy.add(newSeries);
            return new DataFrame(seriesCopy);
        }

    }

    DataFrame addRow(String[] dataRow, boolean inPlace) {
        if (inPlace) {
            for (int i = 0; i < dataRow.length; i++) {
                columns.get(i).values.add(dataRow[i]);
            }
            return this;
        } else {
            DataFrame clone = new DataFrame(columns);
            clone.addRow(dataRow, true);
            return clone;
        }
    }

    public DataFrame get(String[] cols, boolean copy) {
        if (copy) {
            DataFrame df = new DataFrame(columns);
            List<Series> seriesCopy = new ArrayList<>(columns);

            for (int i = 0; i < cols.length; i++) {
                seriesCopy.get(i).setName(cols[i]);
            }
            return new DataFrame(seriesCopy);
        } else {
            for (int i = 0; i < cols.length; i++) {
                columns.get(i).setName(cols[i]);
            }
            return this;
        }
    }

    public Series get(String columnName) {
        return this.columns.stream().filter(col -> col.getName().equals(columnName)).findFirst().orElse(null);
    }

    public void ilocSet(int i, String c, String value) {
        this.columns.stream().filter(series -> series.getName().equals(c)).findFirst().ifPresent(s -> s.getValues().set(i, value));
    }

    public List iloc(int index) {
        return this.columns.stream().map(serie -> serie.getValues().get(index)).collect(Collectors.toList());
    }

    public void iloc2 (int one, int two){
        int i;
        for (i = one; i <= two; i++){
            System.out.println(iloc(i));
        }
    }

    public void printDataFrame() {
        for (Series series : columns) {
            System.out.print(series.getName() + "\t\t");
        }
        System.out.println();
        String helper;
        for (int r = 0; r < size(); r++) {
            for (Series column : columns) {
                helper = column.getValues(r);
                System.out.print(helper + "\t\t\t");
            }
            System.out.println();
        }
    }

    void ReadFile() throws IOException {
        FileInputStream fstream = new FileInputStream("C:\\Users\\homen\\IdeaProjects\\JavaDataFrame\\src\\pl\\edu\\uj\\javaDataFrame\\data.csv");
        BufferedReader br = new BufferedReader(new InputStreamReader(fstream));

        String strLine;

//Read File Line By Line
        while ((strLine = br.readLine()) != null)   {
            // Print the content on the console
            System.out.println (strLine);
        }

//Close the input stream
        br.close();
    }


}


