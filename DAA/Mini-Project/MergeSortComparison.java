import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;

public class MergeSortComparison {

    public static void main(String[] args) {
        System.out.println("Comparing Regular and Multithreaded Merge Sort");
        System.out.println("=============================================");

        int[] arraySizes = { 10000, 100000, 1000000 };
        for (int size : arraySizes) {
            runComparison(size);
        }

        System.out.println("Best and Worst Case Analysis");
        System.out.println("============================");
        analyzeBestWorstCase();
    }

    public static void merge(int[] arr, int left, int mid, int right) {
        int[] temp = new int[right - left + 1];
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }

        while (i <= mid) {
            temp[k++] = arr[i++];
        }

        while (j <= right) {
            temp[k++] = arr[j++];
        }

        System.arraycopy(temp, 0, arr, left, temp.length);
    }

    public static void mergeSort(int[] arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    static class ParallelMergeSort extends RecursiveAction {
        private final int[] array;
        private final int left;
        private final int right;
        private final int threshold;

        ParallelMergeSort(int[] array, int left, int right, int threshold) {
            this.array = array;
            this.left = left;
            this.right = right;
            this.threshold = threshold;
        }

        @Override
        protected void compute() {
            if (right - left <= threshold) {
                mergeSort(array, left, right);
                return;
            }

            int mid = left + (right - left) / 2;
            ParallelMergeSort leftTask = new ParallelMergeSort(array, left, mid, threshold);
            ParallelMergeSort rightTask = new ParallelMergeSort(array, mid + 1, right, threshold);

            invokeAll(leftTask, rightTask);
            merge(array, left, mid, right);
        }
    }

    public static void parallelMergeSort(int[] arr) {
        int threshold = 1000; // Adjust this value based on your system and array sizes
        ForkJoinPool pool = ForkJoinPool.commonPool();
        pool.invoke(new ParallelMergeSort(arr, 0, arr.length - 1, threshold));
    }

    public static int[] generateRandomArray(int size) {
        Random rand = new Random();
        int[] arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = rand.nextInt(1000000);
        }
        return arr;
    }

    public static long measureTime(Runnable task) {
        long startTime = System.nanoTime();
        task.run();
        long endTime = System.nanoTime();
        return endTime - startTime;
    }

    public static void runComparison(int arraySize) {
        int[] arr = generateRandomArray(arraySize);
        int[] arrCopy = Arrays.copyOf(arr, arr.length);

        System.out.println("Array size: " + arraySize);

        long regularTime = measureTime(() -> mergeSort(arr, 0, arr.length - 1));
        System.out.printf("Regular Merge Sort time: %.6f seconds%n", regularTime / 1e9);

        long parallelTime = measureTime(() -> parallelMergeSort(arrCopy));
        System.out.printf("Parallel Merge Sort time: %.6f seconds%n", parallelTime / 1e9);

        double speedup = (double) regularTime / parallelTime;
        System.out.printf("Speedup: %.2fx%n%n", speedup);
    }

    public static void analyzeBestWorstCase() {
        System.out.println("Best Case Analysis (Already Sorted Array):");
        int[] bestCase = new int[100000];
        for (int i = 0; i < bestCase.length; i++) {
            bestCase[i] = i;
        }
        runComparison(bestCase.length);

        System.out.println("Worst Case Analysis (Reverse Sorted Array):");
        int[] worstCase = new int[100000];
        for (int i = 0; i < worstCase.length; i++) {
            worstCase[i] = worstCase.length - i - 1;
        }
        runComparison(worstCase.length);
    }
}