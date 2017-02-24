BEGIN { IGNORECASE=1 }
NR==FNR {
    a[$0]++
    next
}
{
    for (i in a) 
        if (index($0,i)) 
            delete a[i]
}

END {
    for (i in a)
        print i
}
