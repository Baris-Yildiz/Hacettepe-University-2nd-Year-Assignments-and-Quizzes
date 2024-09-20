import org.knowm.xchart.*;
import org.knowm.xchart.style.Styler;
import java.io.IOException;
import java.util.*;

class Main {
    public static void main(String[] args) throws IOException {
        String fileName = args[0];
        SortingExperiment sortingExperiment = new SortingExperiment(fileName);
        System.out.println("The Sorting Experiment: ");
        double[][] sortData1 = sortingExperiment.testSortingAlgorithms(false, false);
        double[][] sortData2 = sortingExperiment.testSortingAlgorithms(true, false);
        double[][] sortData3 = sortingExperiment.testSortingAlgorithms(true, true);

        SearchingExperiment searchingExperiment = new SearchingExperiment(fileName);
        searchingExperiment.setSortedDataList(sortingExperiment.getSortedDataList());
        
        System.out.println("The Searching Experiment: ");
        double[][] searchData = searchingExperiment.testSearchingAlgorithms();

        int[] inputAxis = {500, 1000, 2000, 4000, 8000, 16000, 32000, 64000, 120000, 250000};
        String[] sortLabels =  new String[]{"Insertion Sort", "Merge Sort", "Counting Sort"};
        String[] searchLabels = new String[]{"Linear Search on Random Data", "Linear Search on Sorted Data", "Binary Search"};

        showAndSaveChart("Sorting Test on Random Data", inputAxis, sortData1, sortLabels,"Time in Milliseconds");
        showAndSaveChart("Sorting Test on Sorted Data", inputAxis, sortData2, sortLabels, "Time in Milliseconds");
        showAndSaveChart("Sorting Test on Reversely Sorted Data", inputAxis, sortData3,sortLabels, "Time in Milliseconds");
        showAndSaveChart("Searching Test", inputAxis, searchData, searchLabels, "Time in Nanoseconds");
    }

    public static void showAndSaveChart(String title, int[] xAxis, double[][] yAxis, String[] labels, String yAxisTitle) throws IOException {
        // Create Chart
        XYChart chart = new XYChartBuilder().width(800).height(600).title(title)
                .yAxisTitle(yAxisTitle).xAxisTitle("Input Size").build();

        // Convert x axis to double[]
        double[] doubleX = Arrays.stream(xAxis).asDoubleStream().toArray();

        // Customize Chart
        chart.getStyler().setLegendPosition(Styler.LegendPosition.InsideNE);
        chart.getStyler().setDefaultSeriesRenderStyle(XYSeries.XYSeriesRenderStyle.Line);

        // Add a plot for a sorting algorithm
        chart.addSeries(labels[0], doubleX, yAxis[0]);
        chart.addSeries(labels[1], doubleX, yAxis[1]);
        chart.addSeries(labels[2], doubleX, yAxis[2]);


        // Save the chart as PNG
        BitmapEncoder.saveBitmap(chart, title + ".png", BitmapEncoder.BitmapFormat.PNG);

        // Show the chart
        new SwingWrapper(chart).displayChart();
    }
}
