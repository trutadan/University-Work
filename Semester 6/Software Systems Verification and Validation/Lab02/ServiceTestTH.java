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

    }

    @AfterEach
    void tearDown() {
        service.deleteStudent("asdf");
    }

    @Test
    void test_saveStudent__CorrectGroupValidIDValidNameValidEmailFormatValidProfessorName__Valid() {
        String id = "asdf";
        String nume = "Nume";
        int grupa = 937;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(1, service.saveStudent(id, nume, grupa, email, professorName));

    }
    @Test
    void test_saveStudent__NegativeGroupValidIdValidNameValidEmailFormatValidProfessorName__Invalid() {
        String id = "asdf";
        String nume = "Nume";
        int grupa = -1;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(0, service.saveStudent(id, nume, grupa, email, professorName));

    }
    @Test
    void test_saveStudent__CorrectGroupEmptyIdValidNameValidEmailFormatValidProfessorName__Invalid() {
        String id = "";
        String nume = "Nume";
        int grupa = 937;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(0, service.saveStudent(id, nume, grupa, email, professorName));
    }
    @Test
    void test_saveStudent__CorrectGroupValidIdEmptyNameValidEmailFormatValidProfessorName__Invalid() {
        String id = "asdf";
        String nume = "";
        int grupa = 937;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(0, service.saveStudent(id, nume, grupa, email, professorName));
    }
    @Test
    void test_saveStudent__CorrectGroupValidIdValidNameEmptyEmailValidProfessorName__Invalid() {
        String id = "asdf";
        String nume = "Nume";
        int grupa = 937;
        String email = "";
        String professorName = "Professor1";
        assertEquals(0, service.saveStudent(id, nume, grupa, email, professorName));
    }
    @Test
    void test_saveStudent__CorrectGroupValidIdValidNameValidEmailFormatEmptyProfessorName__Invalid() {
        String id = "asdf";
        String nume = "Nume";
        int grupa = 937;
        String email = "imail@imail.co.uk";
        String professorName = "";
        assertEquals(0, service.saveStudent(id, nume, grupa, email, professorName));
    }
    @Test
    void test_saveStudent__CorrectGroupValidIdValidNameInvalidEmailFormatValidProfessorName__Invalid() {
        String id = "asdf";
        String nume = "Nume";
        int grupa = 937;
        String email = "imail@imail";
        String professorName = "Professor1";
        assertEquals(0, service.saveStudent(id, nume, grupa, email, professorName));
    }
    @Test
    void test_saveStudent__IncorrectGroupValidIDValidNameValidEmailFormatValidProfessorName__Invalid(){
        String id = "asdf";
        String nume = "Nume";
        int grupa = 1000;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(0, service.saveStudent(id, nume, grupa, email, professorName));
    }


    @Test
    void BVATest_saveStudent__GroupEqualTo100__Invalid() {
        String id = "asdf";
        String nume = "Nume";
        int grupa = 100;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(0, service.saveStudent(id, nume, grupa, email, professorName));
    }

    @Test
    void BVATest_saveStudent__GroupEqualTo111__Valid() {
        String id = "asdf";
        String nume = "Nume";
        int grupa = 111;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(1, service.saveStudent(id, nume, grupa, email, professorName));
    }

    @Test
    void BVATest_saveStudent__GroupEqualTo112__Valid() {
        String id = "asdf";
        String nume = "Nume";
        int grupa = 112;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(1, service.saveStudent(id, nume, grupa, email, professorName));
    }

    @Test
    void BVATest_saveStudent__GroupEqualTo422__Valid() {
        String id = "asdf";
        String nume = "Nume";
        int grupa = 422;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(1, service.saveStudent(id, nume, grupa, email, professorName));
    }

    @Test
    void BVATest_saveStudent__GroupEqualTo936__Valid() {
        String id = "asdf";
        String nume = "Nume";
        int grupa = 936;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(1, service.saveStudent(id, nume, grupa, email, professorName));
    }

    @Test
    void BVATest_saveStudent__GroupEqualTo938__Invalid() {
        String id = "asdf";
        String nume = "Nume";
        int grupa = 938;
        String email = "imail@imail.co.uk";
        String professorName = "Professor1";
        assertEquals(0, service.saveStudent(id, nume, grupa, email, professorName));
    }


}