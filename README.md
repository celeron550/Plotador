# 📈 Plotador

**Plotador** é uma aplicação gráfica desenvolvida em C++ com Qt, destinada à visualização de funções matemáticas através da plotagem de seus gráficos cartesianos. A ferramenta permite a entrada de expressões matemáticas e exibe suas curvas com precisão e clareza, sendo ideal para fins educacionais.

> ⚠️ **Atenção:** Este projeto fez parte de uma **avaliação da disciplina de Programação Avançada (DCA3303)**. O código foi submetido a um software detector de plágio. **Não é recomendado copiar qualquer trecho deste repositório para fins acadêmicos**, pois isso pode ser facilmente detectado.

---

## 🛠️ Tecnologias Utilizadas

- **Linguagem:** C++
- **Framework:** Qt 
- **Sistema de build:** QMake

---


## 🚀 Como Compilar

> **Pré-requisitos:**
> - Qt 6 instalado (incluindo Qt Creator)
> - C++14 ou superior configurado

### 🔧 Usando o Qt Creator (recomendado)

1. Clone o repositório:
   ```bash
   git clone https://github.com/celeron550/Plotador.git
   cd Plotador
    ```
2. Abra o arquivo Plotador.pro no Qt Creator.

3. Compile e execute o projeto clicando em Run.
## 🖥️ Alternativa via terminal (Linux)

```bash
qmake Plotador.pro
make
./Plotador
```
## ✨ Funcionalidades
- Interface gráfica para entrada de funções matemáticas.

- Renderização precisa de eixos e curvas.

- Parsing de expressões com operadores básicos (`+`, `-`, `*`, `/`, `^`).

- Tratamento de erros na entrada da função.

## 📄 Licença
Este projeto não possui uma licença definida. Uso para fins acadêmicos é desencorajado devido à natureza da avaliação mencionada.

## 🤝 Contribuições
Contribuições são bem-vindas! Caso deseje melhorar o projeto, envie um pull request ou abra uma issue com sua sugestão.
