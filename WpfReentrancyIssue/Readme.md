I heard lot about Reentrancy issues in WCF/WPF in one of the project which i am working,  
But did not find any simple example in internet. Hence tried to make one myself to demonstrate idea on what is Reentrancy problem.  


Download and compile the Project  
Launch application and enter any value in Text box.  
Application will crash beacuse of stack overflow exception.  

Cause of stack overflow (Due to Reentrancy):-  
While setting the value in textbox ex:- AB  
WPF Triggers viewmodel.Text property to set a value "AB" and changes Text via TextBoxTextChanged.  
Property value set in viewmodel and INotifyPropertyChanged.PropertyChanged event is triggered.  
Execution re-enters the callback via TextBoxTextChanged before the one in the callstack had a chance to finish.  
Recursive logic without stop-case causes eventual stack overflow.  


![Exception](screenshot.PNG)






inspired by article  

https://github.com/dmitry-a-morozov/fsharp-wpf-mvc-series/wiki/Reentrancy-problem
