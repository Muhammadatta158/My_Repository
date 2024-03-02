struct SComplex
{
    double R;//Real part
    double I;//Imaginary part
};
struct SComplex Read(char name[])
{
    struct SComplex c;
    printf("Enter %s complex value (EX: 5,-3): ",name);
    scanf("%lf,%lf",&c.R,&c.I);
    return c;
};
struct SComplex Add(struct SComplex A, struct SComplex B)
{
    struct SComplex c;
    c.R=A.R+B.R;
    c.I=A.I+B.I;
    return c;
};
void print(char name[],struct SComplex c)
{
    printf("%s=(%lf)+j(%lf)",name,c.R,c.I);
}
void main()
{
    struct SComplex X,Y,Z;
    X=Read("X");
    Y=Read("Y");
    Z=Add(X,Y);
    print("Z",Z);
}
