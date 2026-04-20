# Usamos uma imagem base leve e focada em performance
FROM gcc:latest

# Instalamos Python para rodar o seu gerador de ruído (generator.py)
RUN apt-get update && apt-get install -y python3 python3-pip

# Definimos o diretório de trabalho
WORKDIR /usr/src/firewall_assintotico

# Comando padrão: apenas mantém o container vivo para você entrar
CMD ["tail", "-f", "/dev/null"]