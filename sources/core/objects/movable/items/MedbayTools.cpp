#include "MedbayTools.h"

using namespace kv;

HealthAnalyzer::HealthAnalyzer()
{
    SetSprite("icons/device.dmi");
    SetState("health");
    SetName("Health Analyzer");
}

void HealthAnalyzer::Scan(IdPtr<Human> target)
{
    float health = target->GetHealth() / 100.0f;
    float suffocation = target->GetSuffocationDamage() / 100.0f;
    float burn = target->GetBurnDamage() / 100.0f;
    float brute = target->GetBruteDamage() / 100.0f;
    float toxins = target->GetToxinsDamage() / 100.0f;

    // TODO: that should done with one call of PostHtmlFor
    // Just one big string should be made

    PostHtmlFor(
        QString("<b>Analyzing results for %1:</b>").arg(target->GetName().toHtmlEscaped()),
        GetOwner());
    PostHtmlFor("Overall status:", GetOwner());

    QString healthy = QString("<b>%1%</b> healthy").arg(health);
    QString deceased("<b><font color=\"red\">Deceased</font></b>");

    PostHtmlFor(target->IsDead() ? deceased : healthy, GetOwner());
    if (target->GetBruteDamage() > HUMAN_MAX_HEALTH / 10)
    {
        QString level = target->GetBruteDamage() > (HUMAN_MAX_HEALTH / 2) ? "Severe" : "Minor";
        PostHtmlFor(
            QString("%1 <font color=\"red\">tissue damage</font> detected.").arg(level),
            GetOwner());
    }
    if (target->GetBurnDamage() > HUMAN_MAX_HEALTH / 10)
    {
        QString level = target->GetBurnDamage() > (HUMAN_MAX_HEALTH / 2) ? "Severe" : "Minor";
        PostHtmlFor(
            QString("%1 <font color=\"#7f8200\">burn damage</font> detected.").arg(level),
            GetOwner());
    }
    if (target->GetToxinsDamage() > HUMAN_MAX_HEALTH / 10)
    {
        QString level = target->GetToxinsDamage() > HUMAN_MAX_HEALTH / 2 ? "Severe" : "Minor";
        PostHtmlFor(
            QString("%1 <font color=\"green\">intoxication</font> detected.").arg(level),
            GetOwner());
    }
    if (target->GetSuffocationDamage() > HUMAN_MAX_HEALTH / 10)
    {
        QString level = target->GetSuffocationDamage() > HUMAN_MAX_HEALTH / 2 ? "Severe" : "Minor";
        PostHtmlFor(
            QString("%1 <font color=\"blue\">oxygen deprivation</font> detected.").arg(level),
            GetOwner());
    }
    PostHtmlFor(
        QString("Damage: <font color=\"red\">Brute</font>-"
                "<font color=\"#7f8200\">Burn</font>-"
                "<font color=\"green\">Toxins</font>-"
                "<font color=\"blue\">Suffocation</font>"
                " Specfics: <b><font color=\"red\">%1%</font></b>-"
                "<b><font color=\"#7f8200\">%2%</font></b>-"
                "<b><font color=\"green\">%3%</font></b>-"
                "<b><font color=\"blue\">%4%</font></b><br>")
            .arg(brute).arg(burn).arg(toxins).arg(suffocation),
        GetOwner());
}
Medicine::Medicine()
{
    burn_heal_ = 0;
    brute_heal_ = 0;
    toxins_heal_ = 0;
}

void Medicine::Heal(IdPtr<Human> target)
{
    target->ApplyBurnDamage(-1 * burn_heal_);
    target->ApplyBruteDamage(-1 * brute_heal_);
    target->ApplyToxinsDamage(-1 * toxins_heal_);
    Delete();
}

Ointment::Ointment()
{
    SetState("ointment");
    burn_heal_ = 1000;
    SetName("Ointment");
}

BruisePack::BruisePack()
{
    SetState("brutepack");
    brute_heal_ = 1000;
    SetName("Bruise pack");
}

AntitoxinBottle::AntitoxinBottle()
{
    SetSprite("icons/chemical.dmi");
    SetState("bottle17");
    toxins_heal_ = 1000;
    SetName("Anti-Toxin bottle");
}
