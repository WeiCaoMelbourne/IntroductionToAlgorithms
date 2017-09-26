
int Button_up_cut_rod(int* price_list, int len, int n)
{
    int r[n], s[n];
    r[0] = 0;
    
    int j = 0;
    for (; j < n; j ++)
    {
        int q = -1;
        int i = 0;
        s[j] = j;
        for (; i <= j; i++)
        {
            if (q < p[i] + r[j - i])
            {
                q = p[i] + r[j - i];
                s[j] = i;
            }
        }
        r[j] = q;
    }

    return r[n];
}

int main()
{
    int price_list[10] = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int p = Button_up_cut_rod(price_list, sizeof(price_list)/sizeof(int), 5);
    printf("When n = 5, p = %d\n", p);
}