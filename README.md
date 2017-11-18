# Student-Information-System

A simple example of link list to deal with student information.

This is a project of the class (210522, USTC) for which I work as TA.

The program was written in two versions, `C` and `C++`. By and large, they are the same, having functions like creation, inserting, deleting and others. The only difference is the `C++` version doesn’t support the file operation temporary. In code, they shared the same header files, and the included part is decided by whether the macro name `__cplusplus` is defined.

In the `C++` part, the template class is used, so it can be changed easily when it needs other use. While in the `C` part, the link list is written no more different with what people always see, but a `typedef` is stated in the `cnode.h`, so that the user can change the data type of the data domain of the node. Although the user must remember to write the definition of the `struct NodeData` before including this header file. Also, the first actual parameter in the functions whose corresponding version in `C++` is the class's member functions, are named as `this`, which makes it more like `C++`. It is worth mentioning that these functions are defined as `inline`, so that it can be defined in the header files, without redefinitions while reincluded. In fact, member functions of a class are defined as inline too, by default.

What can be modified in the project is that the link list can be changed into **intrusive linked list**. Of course, it may take lots of time to finish this work, and more importantly, it is far beyond the syllabus of this class.
