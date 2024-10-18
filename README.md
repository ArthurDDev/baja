# Como rodar

### back-end

##### criando a database

1. rode os seguintes comandos dentro da interface da mariadb
```
create database nome_da_database;
create user 'nome_do_user'@localhost identified by 'senha_segura';
grant all privileges on nome_da_database.* to 'nome_do_user'@localhost;
flush privileges;
```
2. substitua os itens nome_da_database, nome_do_user e senha_segura

3. Dentro do diretório do back-end, copie o arquivo .env.example e altere os dados da database para os que você escolheu acima.

##### Instalando dependências

Rode o comando
```
composer install
```

##### Fazendo o deploy

1. Certifique-se que o projeto está no diretório /var/www/html/, ou crie um link simbólico

2. Rode os comandos

```
php artisan migrate:fresh
php artisan passport:install
php artisan key:generate
```

E pronto, é para o back-end estar configurado

### front-end

1. Instale as dependências
```
npm install
```
MUITO CUIDADO COM ESSA PARTE. SE O SEU COMPUTADOR TIVER POUCA MEMORIA VAI DAR ERRO

2. Crie a build
```
npm run build
```

3. Inicie o pm2
```
pm2 start script.json --watch
```

### Colocando tudo no ar

1. Criando a configuração do nginx

crie um arquivoprojeto.conf-back em /etc/nginx/sites-avaible e coloque o seguinte:
```
server {
         listen 8000;
         listen [::]:8000;


         # Log files for Debugging
         access_log /var/log/nginx/laravel-access.log;
         error_log /var/log/nginx/laravel-error.log;

         # Webroot Directory for Laravel project
         root /var/www/html/NOME_DA_PASTA/back-end/public;
         index index.php index.html index.htm;


         location / {
                 try_files $uri $uri/ /index.php?$query_string;
         }

         # PHP-FPM Configuration Nginx
         location ~ \.php$ {
                 try_files $uri =404;
                 fastcgi_split_path_info ^(.+\.php)(/.+)$;
                 fastcgi_pass unix:/var/run/php/phpVERSÃO_DO_PHP-fpm.sock;
                 fastcgi_index index.php;
                 fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
                 include fastcgi_params;
         }
    }
```

Faça o mesmo com o front, no arquivo projeto.conf-front:
```
server{
    server_name DOMINIO_DO_PROJETO.com;

    index index.php index.html index.htm;

location / {
        proxy_pass http://localhost:3000/;
        proxy_http_version 1.1;
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection 'upgrade';
        proxy_set_header Host $host;
        proxy_cache_bypass $http_upgrade;
    }

 }
```

PELOAMORDEDEUS nao esqueça de mudar os nomes

2. Crie um link simbólico para o diretório sites-enabled/
```
ln -s /etc/nginx/sites-available/projeto.conf-back /etc/nginx/sites-enabled/;
ln -s /etc/nginx/sites-available/projeto.conf-front /etc/nginx/sites-enabled/
```

3. Inicie o nginx
```
systemctl restart nginx
```
