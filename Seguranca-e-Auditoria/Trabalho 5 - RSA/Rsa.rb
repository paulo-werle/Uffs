# Faz validação para divisão
def divisao a, b
  b != 0 ? a / b : a
end
# Faz validação para mod
def mod a, b
  b != 0 ? a % b : a
end

# Calcula o totient
def totient n
  result = n
  i = 2
  while (i * i) <= n do
    if mod(n , i) == 0
      while mod(n , i) == 0 do
        n = divisao(n , i)
      end
      result -= divisao(result , i)
    end
    i += 1
  end
  result -= divisao(result, n) if n > 1
  return result;
end

# Faz exponecialização
def expoentes p, q, m
  r = 1
  while q != 0 do
    r = (r * p) % m if ![false, 0].include?(q & 1)
    p = (p * p) % m
    q >>= 1
  end
  return r
end

def mdc a, b
  if [false, 0].include?(b)
    @x = 1
    @y = 0
    @d = a
    return
  end
  mdc(b, mod(a,b) )
  x1 = @y
  y1 = @x - (a / b) * @y
  @x = x1
  @y = y1

end

def inv_mod a, m
  mdc(a, m)
  (@x % m + m) % m
end

# Pega valores inicias
n, e, c = gets.chomp.split(" ").map(&:to_i)

# Calc totient
totient = totient(n);

# Acha inverso multiplicativo
d = inv_mod(e, totient);

# Faz exponecialização
printf("#{expoentes(c, d, n)}\n");
