# Smooth-interpolation Report
Цель. Сформировать практические навыки аппроксимации табличных функций с помощью сглаживающих сплайнов.

Расчет:
Часть значений, так как выборка размером 1363:
![image](https://github.com/user-attachments/assets/279c84b6-fd5d-4a43-80f2-72341bd93577)

![image](https://github.com/user-attachments/assets/66ed2192-e88b-4c77-848f-d10df280a592)

Для наглядности выборка размером 5:
![image](https://github.com/user-attachments/assets/6c852bf4-41ee-4126-8cfe-c1bf87208801)

![image](https://github.com/user-attachments/assets/a86eec5d-b170-48f8-b46a-9dc7a4acca17)

Так же та же выборка, но веса для всех значений 0.5:
![image](https://github.com/user-attachments/assets/ba64301d-b280-4d1c-a66f-f7584c02beb4)


![image](https://github.com/user-attachments/assets/ea039deb-4872-41bc-9717-48bd36a3eeaf)


При p=0 сглаживающий сплайн начинает работать как интерполяционный
А при p близком к 1 значения сглаживающего сплайна приближаются к среднему
Так же чем меньше вес значений(W) тем ближе значения сглаживающего сплайна к среднему.

Вывод: сглаживающий сплайн может работать интерполяционный, то есть достраивать функцию. А так же, при увеличении P или уменьшении W его значений будут стремиться к среднему по выборке
