FROM python:3

WORKDIR /usr/src/app

COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt

COPY . .

ENV LC_ALL C.UTF-8
ENV LANG C.UTF-8

EXPOSE 8080
CMD [ "python3", "./Anne.py" ]