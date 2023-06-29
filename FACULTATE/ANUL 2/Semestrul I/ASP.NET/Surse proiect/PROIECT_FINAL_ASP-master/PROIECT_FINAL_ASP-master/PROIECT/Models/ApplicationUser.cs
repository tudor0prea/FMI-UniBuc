using Microsoft.AspNetCore.Identity;
using System.ComponentModel;
using System.Runtime.ConstrainedExecution;
using System.Security.Claims;

namespace PROIECT.Models
{
    //PASUL 1

    // mosteneste IdentityUser care are meotdele ce ne intereseaza(numar telefon, sa ne logam cu fb,google) 
    //Clasa pe care o mosteneste, IdentityUser, descrie Userul
    //in baza de date(cea care contine toate atributele unui utilizator).
    //ne ajuta sa extindem user ul daca vrem sa adaugam campuri noi
    public class ApplicationUser : IdentityUser
    {
    }
}
