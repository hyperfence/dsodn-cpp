<h1 align="center">Data Storage over Distributed Networks (C++)</h1> 
<br/><br/>
<p align="center"><strong>Note: This is an educational project created for the sole purpose of self learning.</strong></p>
<br/>
<h2>Introduction</h2>
<p>
Let's consider a scenario where the data is not located on a single machine but rather stored on multiple machines geo-distributed across the Internet. In such a scenario, searching or retrieval of data is very challenging, as it is hard to determine on which machine the required data is stored. This challenge can be solved by using a Data Structure that can efficiently search for data stored on a single machine. We will be mainly using <strong>Hash Tables</strong> along with <strong>Linked Lists</strong> and <strong>Binary Search Trees</strong> to design an efficient solution for this scenario.
</p>
<br/>
<h2>Concept Illustration</h2>
<p align="center">
  <img alt="Concept Illustration" src="https://i.ibb.co/yy2YppP/concept.png" width="600px" height="300px" />
</p>
<br/><br/>
<h2>Implementation</h2>
<p>
  The logic implemetation for this scenario is done using a few initial assumptions. Firstly, all the machines geo-distrubuted across the internet are assumed to be in an identifier space and linked with each other in the form of a circle. Maximum number of machines in this circle depends upon the size of identifier space which is defined initially. A more professional term used for such arrangement is called <strong>"Ring DHT"</strong>. Below is an arbitrary example of machines arranged according to above specification.  
</p>
<p align="center">
  <img alt="Concept Illustration" src="https://i.ibb.co/DQQmnv4/implementation-pic.jpg" width="600px" height="300px" />
</p>
<p>
  On the right side of above picture we have six machines and on the left side the black dots represent these machines in an identifier space. Notice that our identifier space is a sequence which starts from zero and then ends on 15 but then goes from 15 to 0 again and thus forms a circular space. Due to this circular property of our space we call it the Ring DHT where DHT stands for Distributed Hash Tables(we'll discuss about DHTs later). Our identifier space has a size of <strong>4 bits</strong> which means it can hold a maximum of <strong>2^size = 2^4 = 16</strong> machines. In above example out of 16 only 6 machines are currently active in the identifier space. Each of these machines is responsible for holding some sort of data which can be videos, images, music, text files, etc. This data is stored in the form of<strong>key/value</strong> pairs. These key/value pairs are arranged in the form of a Binary Search Tree. Every machine in the above identifier space has a single binary tree used to store data key/value pairs of that machine. 
</p>
<br/><br/>
<h2>Development Team</h2>
<p>
  The entire project was developed and coded by the following team of computer science students:
</p>
<ul>
  <li><a href="https://github.com/malik727">Malik Talha</a></li>
  <li><a href="https://github.com/hammadahmedpk">Hammad Ahmed</a></li>
  <li><a href="https://github.com/Hunaid2000">Hunaid Sohail</a></li>
</ul>
<br/>
<h2>Source</h2>
<p>
  This problem statement was sourced from the semester project given by our university.
</p>
<p>
  <strong>University:</strong> <a href="https://nu.edu.pk">National University of Computer & Emerging Science</a><br/>
  <strong>Problem Statement:</strong> <a href="https://1drv.ms/b/s!AkTG-6TAub7SjSyqoBlyjOHolnQa">PDF File</a>
</p>
