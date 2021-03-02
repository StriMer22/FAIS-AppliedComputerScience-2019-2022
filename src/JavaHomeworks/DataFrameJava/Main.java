package JavaHomeworks.DataFrameJava;

import java.io.IOException;

public class Main {

    public static void main(String[] args) throws IOException {
        DataFrame df = new DataFrame(new String[]{"col1", "col2", "col3"}, new String[]{"int", "double", "float"});
        DataFrame dataFrame = df.get(new String[] {"Number1", "Number2", "Number3"},true);
//        System.out.println(dataFrame.size());
//        dataFrame.addRow(dataFrame.ReadFile(),true);
//        dataFrame.ReadFile();
//        df.printDataFrame();
        df.addColumn("Number4","String",true);
        String[] row = {"1","2","3","4"};
        df.addRow(row,true);
//        df.printDataFrame();
        df.addRow(new String[]{"0","9","2","0"},true);
        df.addRow(new String[]{"8","1","0","0"},true);
        df.addRow(new String[]{"0","0","3","10"},true);

//        df.ilocSet(0,"Number3","4");
//        df.printDataFrame();
//        System.out.println(df.iloc(0) + "\n");
//        System.out.println(df.get("Number2").values + "\n");
//        df.iloc2(0,1);
//        System.out.println("YES");

        SparseDataFrame sparseDataFrame = new SparseDataFrame(df,"0");
        sparseDataFrame.printDataFrame();
        sparseDataFrame.toDense().printDataFrame();
    }
}

