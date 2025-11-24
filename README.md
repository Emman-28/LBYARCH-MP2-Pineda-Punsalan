# [MP2] x86-to-C interface (Grayscale Image Conversion)

### LBYARCH - S19A
**Authors:** 
- Pineda, Dencel Angelo D. 
- Punsalan, Emmanuel Gerald G.

---

### Project Specification
To enable using different image processing libraries simultaneously, conversion from one format to theother has to be done. Perform Mapping from uint8 based integer grayscale to
double precision float representation.

---

### How to Run
1. Open Visual Studio Community 2022.


2. Open Project with the C and ASM files.


4. Press "Build".

5. Press "Debug".

7. Input height, width, and array dimensions.

   You may copy the following sample input:
   ```
   3 4
   64, 89, 114, 84, 140, 166, 191, 84, 216, 242, 38, 84

---

### Notes
- The input pixel values can either be separated with a comma or not.

---

### Program Features
1. Conversion
- Converts 8-bit integer grayscale pixels (0–255) to double-precision floating-point values (0.0–1.0) using an x86 assembly function in collaboration with a C program.

2. Correctness Checking
- Verifies that the converted values match expected normalized values.
- Prints errors per pixel if conversion fails.

3. Performance Checking
- Measures execution time over multiple runs.
- Supports test images of 10×10, 100×100, and 1000×1000 pixels.
- Reports average time per pixel.

4. Use of SIMD registers and instructions
- As per project specifications, registers such as xmm0 and xmm1, and instructions such as cvtsi2sd, divsd, and movsd were used.

---

### Screenshot of Output and Correctness Check
<img width="1436" height="759" alt="image" src="https://github.com/user-attachments/assets/bc9e0d8e-06ae-469f-b1fb-5ae34faea5ad" />

---

### Performance Analysis

Execution Time Results:
The assembly function imgCvtGrayIntToDouble was executed 30 times for each test case to obtain the average execution time. The tests were conducted on varying image dimensions to observe how the program scales with increased data load.

Image Dimension	Total Pixels	Average Execution Time	
   10 x 10	           100	            0.000000s	         
   100 x 100	       10,000	         0.000067s	
  1000 x 1000	     1,000,000	         0.008833s

Analysis:
The performance tests demonstrate a clear linear growth in the average execution time, where execution times increased proportionally from 0.000067s for 10,000 pixels to 0.008833s for 1,000,000 pixels. By using specialized assembly instructions to handle the math directly on the processor, the code avoids unnecessary delays, allowing it to process even one million pixels in just a fraction of a second (about 8 nanoseconds per pixel). This stability shows that our low-level approach remains efficient and consistent regardless of how much data is processed.

---
### Video Demo
https://youtu.be/s0JzCR39ygo
