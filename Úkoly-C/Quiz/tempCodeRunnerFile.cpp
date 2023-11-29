while(getline(myFile, radek))
        {
            stringstream ss(radek);
            getline(ss, question.question, ';' );
            getline(ss, question.a, ';' );
            getline(ss, question.b, ';' );
            getline(ss, question.c, ';' );