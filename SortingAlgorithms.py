tab = [9,8,7,6,5,4,3,2,1]


def mergeSort(tab):
    if len(tab) <= 1:
        return tab
    tabL = mergeSort(tab[0:len(tab)//2])
    tabR = mergeSort(tab[len(tab)//2:])
    fusion = []
    while len(tabL) != 0 and len(tabR) != 0:
        if tabL[0] <= tabR[0]:
            fusion.append(tabL.pop(0))
        else:
            fusion.append(tabR.pop(0))
    fusion += tabR + tabL
    return fusion
print(mergeSort(tab))


