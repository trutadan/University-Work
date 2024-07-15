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
        service.deleteStudent("2");
    }

    @Test
    void test_saveStudent__PositiveGroupVaidIDValidName__Valid() {
        String id = "2";
        String nume = "Nume";
        int grupa = 937;
        assertEquals(1, service.saveStudent(id, nume, grupa));

    }
    @Test
    void test_saveStudent__NegativeGroupValidIdValidName__Invalid() {
        String id = "1";
        String nume = "Nume";
        int grupa = -1;
        assertEquals(0, service.saveStudent(id, nume, grupa));

    }

}