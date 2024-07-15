package service;

import domain.Nota;
import domain.Student;
import domain.Tema;
import org.junit.jupiter.api.Test;
import repository.NotaXMLRepository;
import repository.StudentXMLRepository;
import repository.TemaXMLRepository;
import validation.NotaValidator;
import validation.StudentValidator;
import validation.TemaValidator;
import validation.Validator;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class BigBangTest {
    @Test
    void test_saveStudent__CorrectGroupValidIDValidNameValidEmailFormatValidProfessorName__Valid() {
        Service service;

        Validator<Student> studentValidator = new StudentValidator();
        Validator<Tema> temaValidator = new TemaValidator();
        Validator<Nota> notaValidator = new NotaValidator();

        StudentXMLRepository studentXMLRepository = new StudentXMLRepository(studentValidator, "studenti.xml");
        TemaXMLRepository temaXMLRepository = new TemaXMLRepository(temaValidator, "teme.xml");
        NotaXMLRepository notaXMLRepository = new NotaXMLRepository(notaValidator, "note.xml");
        service = new Service(studentXMLRepository, temaXMLRepository, notaXMLRepository);

        String id = "asdf";
        String nume = "Nume";
        int grupa = 937;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(1, service.saveStudent(id, nume, grupa, email, professorName));
        service.deleteStudent("asdf");

    }
    @Test
    void test_saveTema__CorrectDeadlineValidIDValidDescriptionValidStartline__Valid() {
        Service service;

        Validator<Student> studentValidator = new StudentValidator();
        Validator<Tema> temaValidator = new TemaValidator();
        Validator<Nota> notaValidator = new NotaValidator();

        StudentXMLRepository studentXMLRepository = new StudentXMLRepository(studentValidator, "studenti.xml");
        TemaXMLRepository temaXMLRepository = new TemaXMLRepository(temaValidator, "teme.xml");
        NotaXMLRepository notaXMLRepository = new NotaXMLRepository(notaValidator, "note.xml");
        service = new Service(studentXMLRepository, temaXMLRepository, notaXMLRepository);

        String id = "asdf";
        String descriere = "Descriere";
        int deadline = 10;
        int startline = 5;
        assertEquals(1, service.saveTema(id, descriere, deadline, startline));
        service.deleteTema("asdf");

    }

    @Test
    void test_saveNota__CorrectIDStudentValidIDTemaValidNotaValidSaptamanaValidFeedback__Valid() {
        Service service;

        Validator<Student> studentValidator = new StudentValidator();
        Validator<Tema> temaValidator = new TemaValidator();
        Validator<Nota> notaValidator = new NotaValidator();

        StudentXMLRepository studentXMLRepository = new StudentXMLRepository(studentValidator, "studenti.xml");
        TemaXMLRepository temaXMLRepository = new TemaXMLRepository(temaValidator, "teme.xml");
        NotaXMLRepository notaXMLRepository = new NotaXMLRepository(notaValidator, "note.xml");
        service = new Service(studentXMLRepository, temaXMLRepository, notaXMLRepository);

        service.saveStudent("mznxcv", "Nume", 937, "asdah@ymail.com", "Professor1");
        service.saveTema("gugugaga", "Descriere", 10, 5);

        String idStudent = "mznxcv";
        String idTema = "gugugaga";
        double valNota = 10;
        int predata = 10;
        String feedback = "Feedback";
        assertEquals(1, service.saveNota(idStudent, idTema, valNota, predata, feedback));

        service.deleteNota("mznxcv", "gugugaga");
        service.deleteStudent("mznxcv");
        service.deleteTema("gugugaga");

    }
    @Test
    void test_saveStudentAssignmentNota__ValidInputs__Valid(){
        Service service;

        Validator<Student> studentValidator = new StudentValidator();
        Validator<Tema> temaValidator = new TemaValidator();
        Validator<Nota> notaValidator = new NotaValidator();

        StudentXMLRepository studentXMLRepository = new StudentXMLRepository(studentValidator, "studenti.xml");
        TemaXMLRepository temaXMLRepository = new TemaXMLRepository(temaValidator, "teme.xml");
        NotaXMLRepository notaXMLRepository = new NotaXMLRepository(notaValidator, "note.xml");
        service = new Service(studentXMLRepository, temaXMLRepository, notaXMLRepository);

        assertEquals(1,service.saveStudent("mznxcv", "Nume", 937, "asdah@ymail.com", "Professor1"));
        assertEquals(1,service.saveTema("gugugaga", "Descriere", 10, 5));

        String idStudent = "mznxcv";
        String idTema = "gugugaga";
        double valNota = 10;
        int predata = 10;
        String feedback = "Feedback";
        assertEquals(1, service.saveNota(idStudent, idTema, valNota, predata, feedback));
        service.deleteNota("mznxcv", "gugugaga");
        service.deleteStudent("mznxcv");
        service.deleteTema("gugugaga");

    }
}


