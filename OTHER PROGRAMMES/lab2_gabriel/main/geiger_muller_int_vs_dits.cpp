#include "data_colector.cpp"

int main(){

    data_colector gm("dist_data.txt");
    vector<double> x = gm.get_a_certain_col(1);
    double ex_arr[x.size()] = {0};
    vector<double> y = gm.get_a_certain_col(2);
    vector<double> ey = gm.get_a_certain_col(3);
    Int_t points_numb = x.size();

    for (int i = 0; i < x.size(); i++){

        x[i] = x[i] * 100;
    }

    double* x_ptr = &x[0];
    double* y_ptr = &y[0];
    double* ey_ptr = &ey[0];

    TApplication* A = new TApplication("A", 0, 0);
    TCanvas* C = new TCanvas("C", "Canvas", 16*70, 9*70);
    TGraphErrors* g = new TGraphErrors(points_numb, x_ptr, y_ptr, ex_arr, ey_ptr);
    TF1* f = new TF1("f", "[0] / pow(x * 0.01 + [1], 2)");
    //TF1* f = new TF1("f", "[0] * (1 - (x * 0.01 + [2]) / TMath::Sqrt(pow(x * 0.01 + [2], 2) + pow([1], 2)))");
    TPaveText* pt = new TPaveText(3.8, 500, 5.7, 900, "user");

    /*f->SetParameter(0, 2.497 * pow(10, -6) * 3.7 * pow(10, 10) * 1 / (2 * M_PI));
    f->SetParameter(1, 0.015875);*/
    //f->SetParameter(2, 44);

    pt->SetTextSize(0.032);
    pt->SetFillColor(0);
    pt->SetTextAlign(12);
    pt->SetTextFont(42);
    g->SetMarkerStyle(4);
    g->SetMarkerColor(kBlack);
    g->GetXaxis()->SetTitle("Distance to detector entrance (cm)");
    g->GetXaxis()->SetLimits(1, 5.8);
    g->GetXaxis()->SetNdivisions(-412);
    g->GetXaxis()->SetLabelSize(0.028);
    g->GetYaxis()->SetTitle("Count rate (counts/s)");
    g->GetYaxis()->SetRangeUser(50, 1000);
    g->GetYaxis()->SetNdivisions(-219);
    g->GetYaxis()->SetLabelSize(0.028);
    f->SetLineColor(kCyan);

    g->Draw("AP");
    g->Fit("f");
    pt->AddText(Form("y = (\\frac{a}{(r + c)^{2}}) (S.I.)"));
    pt->AddText(Form("a = (%.3f \\pm %.3f) (S.I.)", f->GetParameter(0), f->GetParError(0)));
    //pt->AddText(Form("b = (%.1f \\pm %.1f) (S.I.)", f->GetParameter(1), f->GetParError(1)));
    pt->AddText(Form("c = (%.4f \\pm %.4f) (S.I.)", f->GetParameter(1), f->GetParError(1)));
    pt->AddText(Form("\\chi^{2} = %.1f", f->GetChisquare()));
    /*pt->AddText(Form("y = (b\\times(1 - \\frac{r + c}{\\sqrt{((r + c)^{2} + a^{2})}})) (S.I.)"));
    pt->AddText(Form("b = (%.0f \\pm %.0f) (S.I.)", f->GetParameter(0), f->GetParError(0)));
    pt->AddText(Form("a = (%.3f \\pm %.3f) (S.I.)", f->GetParameter(1), f->GetParError(1)));
    //pt->AddText(Form("u = (%.1f \\pm %.1f) (S.I.)", f->GetParameter(2), f->GetParError(2)));
    pt->AddText(Form("c = (%.4f \\pm %.4f) (S.I.)", f->GetParameter(2), f->GetParError(2)));
    pt->AddText(Form("\\chi^{2} = %.1f", f->GetChisquare()));*/
    pt->Draw();

    C->Update();
    C->SaveAs("gm_fit.png");
    gSystem->ProcessEvents();
    C->WaitPrimitive();

    delete C;
    delete g;
    delete f;
    delete pt;
    delete A;

    return 0;
}