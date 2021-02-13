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
  This section explains the logical implementation of this project.  
</p>
<h3>Identifier Space Concept</h3>
<p>
  In our implementation we assume that all the machines geo-distrubuted across the internet are present in an identifier space and linked with each other in the form of a circle. Maximum number of machines in this circle depends upon the size of the identifier space which is defined once initially in the beginning. A more professional term used for such arrangement is called <strong>"Ring DHT"</strong>. Below is an arbitrary example of machines arranged according to above specification.  
</p>
<p align="center">
  <img alt="Identifier Space" src="https://i.ibb.co/DQQmnv4/implementation-pic.jpg" width="600px" height="300px" />
</p>
<p>
  On the right side of above picture we have six machines and on the left side the black dots represent these machines in the identifier space. The above identifier space has a size of <strong>4 bits</strong> which means it can hold a maximum of <strong>2^size = 2^4 = 16</strong> machines. Notice that our identifier space has 6 out of 16 machines active which are connected with each other in the form of a circle. Due to this circular property of our space we call it the Ring DHT where DHT stands for Distributed Hash Tables(we'll discuss about DHTs later). In the above picture, each active machine has a unique id assigned to it which tells it apart from other machines in the identifier space. In above case 3, 5, 8, 10, 13 and 14 are the ids assigned to the machines respectively.
</p><br/>
<h3>Data Storage Concept</h3>
<p>
 These machines in the identifier space are responsible for holding some sort of data which can be videos, images, music, text files, etc. For the sake of simplicity the data is stored in the form of <strong>key/value</strong> pairs. These key/value pairs are taken input from the user and are arranged in the form of a <strong>Binary Search Tree</strong>. Every active machine in the above identifier space has a single binary tree associated with it which is used to store data key/value pairs of that machine. The key or value can by anything, it can be in the form of a string or a number, for example, a user can enter "Good Movie" as key and "Toy Story 3" as its value. Now this key will be hashed through a hash function and the result from that function will map the value "Toy Story 3" to a specific active machine in the identifier space. This result from hash function will have specific rules, firstly that result will be an integer value so that it can easily be compared with the machine ids and lastly this result will always be a value that falls in the size of the identifier space(eg. in the case above the result will be from 0 to 15 only). In our case consider that key hashed to 10, if you look in the identifier space above there is an active machine with id 10, so, the value "Toy Story 3" will be stored on that machine. But what if the key hashed to a value whose machine is not active like 11, 12 or 0? The answer to this question is quite simple, earlier we said that a machine can store more than one data key/value pairs now let us see how exactly it can store them. Let's assume that after entering the "Good Movie" as key and "Toy Story 3" as value the user enters the following key/value pairs:
</p>
<ul>
  <li><strong>Key:</strong> "Awesome Game"&nbsp;&nbsp;&nbsp;<strong>Value:</strong> "Witcher III"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<strong>[Hashed Key = 0]</strong></li>
  <li><strong>Key:</strong> "A Document"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<strong>Value:</strong> "My Passport"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<strong>[Hashed Key = 9]</strong></li>
  <li><strong>Key:</strong> "Best TV Show"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<strong>Value:</strong> "Peaky Blinders"&nbsp;&nbsp;&nbsp;<strong>[Hashed Key = 15]</strong></li>
</ul>
<p>
  The data "Witcher III", "My Passport" & "Peaky Blinders" will be stored on machines 3, 10 & 3 respectively. From this we can deduce that each active machine is responsible for holding data whose hashed key is either equal to the current machine ID or less than current machine but greater than the ID of predecessor machine. eg. the key "A Document" hashes to 9 but as there is no active machine with id 9, so, the data is stored on the next active machine which is 10.  
</p>
<br/>
<h3>Data Collision Concept</h3>
<p>
  Above we discussed how the data is stored on the active machines of the identifier space but what if more than one key hashes to a same id(eg. "Awesome Game" & "Good Movie" noth hash to value of 10)? In order solve this problem we use the concept of chaining lists. Every node of the binary search tree of a machine holds a singly linked list instead of just holding a single key/value pair. Whenever more than two keys hash to the same id they are inserted in the relevant linked list of BST(Binary Search Tree) of the machine. And to keep track or distinguish a key/value pair of that linked list we use a unique "encryption key" which is associated with every key/value pair of that linked list. This "encryption key" is generated from the same hash function which hashes the simple key to hashed-key. The term DHT which was used earlier is just the concept of hashing a key and then storing its value somewhere. We have already discussed this hashing and storing in detail above.
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
