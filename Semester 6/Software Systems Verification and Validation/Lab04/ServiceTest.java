package service;

import domain.Nota;
import domain.Student;
import domain.Tema;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import repository.NotaXMLRepository;
import repository.StudentXMLRepository;
import repository.TemaXMLRepository;
import validation.NotaValidator;
import validation.StudentValidator;
import validation.TemaValidator;
import validation.Validator;

import static org.junit.jupiter.api.Assertions.*;

class ServiceTest {
    private Service service;

    private Validator<Student> studentValidator = new StudentValidator();
    private Validator<Tema> temaValidator = new TemaValidator();
    private Validator<Nota> notaValidator = new NotaValidator();

    private StudentXMLRepository studentXMLRepository = new StudentXMLRepository(studentValidator, "studenti.xml");
    private TemaXMLRepository temaXMLRepository = new TemaXMLRepository(temaValidator, "teme.xml");
    private NotaXMLRepository notaXMLRepository = new NotaXMLRepository(notaValidator, "note.xml");

    @BeforeEach
    void setUp() {

        service = new Service(studentXMLRepository, temaXMLRepository, notaXMLRepository);
        service.saveStudent("mznxcv", "Nume", 937, "asdah@ymail.com", "Professor1");
        service.saveTema("gugugaga", "Descriere", 10, 5);
    }

    @AfterEach
    void tearDown() {
        service.deleteStudent("asdf");
        service.deleteTema("asdf");
        service.deleteNota("mznxcv", "gugugaga");
        service.deleteStudent("mznxcv");
        service.deleteTema("gugugaga");
    }


    @Test
    void IntegrationTest_saveStudent__CorrectGroupValidIDValidNameValidEmailFormatValidProfessorName__Valid() {
        String id = "asdf";
        String nume = "Nume";
        int grupa = 937;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(1, service.saveStudent(id, nume, grupa, email, professorName));
    }

    @Test
    void IntegrationTest_saveAssignment__CorrectIDValidDescriptionValidDeadlineValidStartline__Valid() {
        String id = "asdf";
        String descriere = "Descriere";
        int deadline = 10;
        int startline = 5;
        String id2 = "asdf";
        String nume = "Nume";
        int grupa = 937;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(1, service.saveStudent(id2, nume, grupa, email, professorName));
        assertEquals(1, service.saveTema(id, descriere, deadline, startline));
    }

    @Test
        void IntegrationTest_saveGrade__CorrectStudentIDCorrectAssignmentIDCorrectGradeCorrectPredataCorrectFeedback__Valid() {
        String idStudent = "asdf";
        service.deleteTema("gugugagaga");
        String idTema = "gugugagaga";
        int grupa = 937;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        String descriere = "Descriere";
        String nume = "Nume";
        int deadline = 10;
        int startline = 5;
        assertEquals(1, service.saveStudent(idStudent, nume, grupa, email, professorName));
        assertEquals(1, service.saveTema(idTema, descriere, deadline, startline));
        double valNota = 10;
        int predata = 10;
        String feedback = "Feedback";
        assertEquals(1, service.saveNota(idStudent, idTema, valNota, predata, feedback));

    }
}