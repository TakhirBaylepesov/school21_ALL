## Part 1. Настройка gitlab-runner

- Поднял виртуальную машину Ubuntu Server 22.04 LTS.

- Скачал и установил на виртуальную машину gitlab-runner.
    1) выполнил команду: <br>
    ```sh
    sudo curl -L --output /usr/local/bin/gitlab-runner https://gitlab-runner-downloads.s3.amazonaws.com/latest/binaries/gitlab-runner-linux-amd64
    ```
    ![part_1](./part_1.2.1.png)

    2) выполнил команду: <br>
    ```sh
    sudo chmod +x /usr/local/bin/gitlab-runner
    ```
    ![part_1](./part_1.2.2.png)

    3) выполнил команду: <br>
    ```sh
    sudo useradd --comment 'Gitlab Runner' --create-home gitlab-runner --shell /bin/bash
    ```
    ![part_1](./part_1.2.3.png)

    4) выполнил команду: <br>
    ```sh
    sudo gitlab-runner install --user=gitlab-runner --working-directory=/home/gitlab-runner
    ```
    ![part_1](./part_1.2.4.png)

    5) выполнил команду: <br>
    ```sh
    sudo gitlab-runner start
    ```
    ![part_1](./part_1.2.5.png)

    6) выполнил команду: <br>
    ```sh
    sudo chown gitlab-runner:gitlab-runner /home/gitlab-runner
    ```
    ![part_1](./part_1.2.6.png)

    7) выполнил команду: <br>
    ```sh
    sudo chmod 700 /home/gitlab-runner
    ```
    ![part_1](./part_1.2.7.png)

- Запустил gitlab-runner и зарегистрировал его для использования в текущем проекте (DO6_CICD).
    1) выполнил команду: <br>
    ```sh
    sudo gitlab-runner register
    ```
    ![part_1](./part_1.3.1.png)

    2) выполнил команду: <br>
    ```sh
    sudo gitlab-runner list
    ```
    ![part_1](./part_1.3.2.png)



## Part 2. Сборка

- Написал этап для CI по сборке приложений из проекта C2_SimpleBashUtils.

    1) Сначала SSH-ключ;
    
    2) Cклонировал проекты C2_SimpleBashUtils и DO6_CICD;

    ![part_2](./part_2.1.1.png)

    ![part_2](./part_2.1.2.png)
    
    3) Скопировал файлы с C2_SimpleBashUtils в DO6_CICD;
    
    ![part_2](./part_2.1.3.png)

- В файле gitlab-ci.yml добавил этап запуска сборки через мейк файл из проекта C2.

    1) создал файл .gitlab-runner.ci.yml

    ![part_2](./part_2.2.png)

- Файлы, полученные после сборки (артефакты), сохранил в произвольную директорию со сроком хранения 30 дней.

    ![part_2](./part_2.3.png)
    
    1) Затем запушил в gutlab

    ![part_2](./part_2.4.png)
    
    2) Проверил в gitlabe раздел CI/CD

    ![part_2](./part_2.5.png)

    3) Посмотрел подробно об ошибке

    ![part_2](./part_2.6.png)

    4) Затем посмотрел скрытые файлы

    ![part_2](./part_2.7.png)

    5) Чтобы исправить ошибку, нужно открыть файл .bash_logout и закомментировать все незакомментированные строки

    ![part_2](./part_2.8.png)

    ![part_2](./part_2.9.png)

    6) Чтобы проверить результат, нужно в gitlabe в разделе CI/CD обновить Run pipeline

    ![part_2](./part_2.10.png)

    7) можно посмотреть результат детально

    ![part_2](./part_2.11.png)



## Part 3. Тест кодстайла

- Написал этап для CI, который запускает clang-format и завершает пайплайн с ошибкой, если кодстайл не прошел.

    1) Для этого нужно изменить файл .gitlab-ci.yml

    ![part_3](./part_3.1.png)

    2) Нужно добавить файл .clang-format для настройки стиля кода

    ![part_3](./part_3.2.png)

    3) После добавления этих файлов, дальше нужно запушить в gitlab

    4) Чтобы проверить результат, нужно в gitlabe перейти в раздел CI/CD

    ![part_3](./part_3.3.png)

    5) можно посмотреть результат детально

    ![part_3](./part_3.4.png)




## Part 4. Интеграционные тесты

- Написал этап для CI, который запускает мои интеграционные тесты из того же проекта.

    1) Для этого нужно изменить файл .gitlab-ci.yml

    ![par_4](./part_4.1.png)

    2) Добавил скрипт в cat и grep

    ![part_4](./part_4.2.png)

    ![part_4](./part_4.4.png)

    3) Добавил тестовые файлы в cat и grep

    ![part_4](./part_4.3.png)

    ![part_4](./part_4.5.png)

    4) После добавления этих файлов, дальше нужно запушить в gitlab



- Запустил этот этап автоматически

![part_4](./part_4.6.png)

- В пайплайне отобразил вывод, что интеграционные тесты успешно прошли

![part_4](./part_4.7.png)


## Part 5. Этап деплоя

- Поднял вторую виртуальную машину Ubuntu Server 22.04 LTS.

![part_5](./part_5.1.1.png)

- Написал этап для CD, который «разворачивает» проект на другой виртуальной машине.

    1) Изменил файл 

    ![part_5](./part_5.1.png)

    2) Сохранил изменения

    ![part_5](./part_5.2.png)

    3) Также изменил во второй машине такой же файл

    ![part_5](./part_5.3.png)

    4) Сохранил изменения

    ![part_5](./part_5.4.png)

    5) Проверил пинг между машинами

    ![part_5](./part_5.5.png) 

    ![part_5](./part_5.6.png)

    6) Подключился ко второй машине по ssh

    ![part_5](./part_5.7.png) 


- В файле gitlab-ci.yml добавил этап запуска написанного скрипта.

![part_5](./part_5.8.png)

- После всего этого, запушил в gitlab.

![part_5](./part_5.9.png)

- Проверил результат deploy

![part_5](./part_5.10.png)



## Part 6. Дополнительно. Уведомления

- Настроил уведомления о успешном выполнении пайплайна через бота с именем hayheadt DO6 CI/CD» в Telegram.

    1) Добавил в файле .gitlab-ci.yml  пункты

    ![part_6](./part_6.1.png)

    2) Добавил скрипт

    ![part_6](./part_6.2.png)

    3) С помощью бота настроил уведомление

    ![part_6](./pary_6.3.png)

    ![part_6](./pary_6.4.png)



